#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <functional>

#include <queryosity.hpp>

#include "TCanvas.h"
#include <ROOT/RVec.hxx>

#include "AnaQuery/Hist.h"
#include "AnaQuery/Tree.h"

template <typename T> using Vec = ROOT::RVec<T>;
using VecUI = Vec<unsigned int>;
using VecI = Vec<int>;
using VecF = Vec<float>;
using VecD = Vec<double>;

using dataflow = queryosity::dataflow;
namespace multithread = queryosity::multithread;
namespace dataset = queryosity::dataset;
namespace column = queryosity::column;
namespace query = queryosity::query;
namespace systematic = queryosity::systematic;

class IsolatedJetSelection
    : public column::definition<VecI(VecF, VecF, VecF, VecF, VecF)> {
public:
  IsolatedJetSelection(float minDR, float pt2Min)
      : m_minDR(minDR), m_pt2Min(pt2Min) {}
  virtual ~IsolatedJetSelection() = default;
  virtual VecI evaluate(column::observable<VecF> eta1,
                        column::observable<VecF> phi1,
                        column::observable<VecF> pt2,
                        column::observable<VecF> eta2,
                        column::observable<VecF> phi2) const override {
    VecI mask(eta1->size(), 1);
    if (eta2->size() == 0) {
      return mask;
    }

    const auto ptcut = (*pt2) > m_pt2Min;
    const auto eta2_ptcut = (*eta2)[ptcut];
    const auto phi2_ptcut = (*phi2)[ptcut];
    if (eta2_ptcut.size() == 0) {
      return mask;
    }

    const auto c = ROOT::VecOps::Combinations(*eta1, eta2_ptcut);
    for (auto i = 0u; i < c[0].size(); i++) {
      const auto i1 = c[0][i];
      const auto i2 = c[1][i];
      const auto dr = ROOT::VecOps::DeltaR((*eta1)[i1], eta2_ptcut[i2],
                                           (*phi1)[i1], phi2_ptcut[i2]);
      if (dr < m_minDR)
        mask[i1] = 0;
    }
    return mask;
  }

protected:
  const float m_minDR;
  const float m_pt2Min;
};

void task(int n) {

  dataflow df(multithread::enable(n));

  std::vector<std::string> tree_files{"Run2012B_SingleMu.root"};
  std::string tree_name = "Events";
  auto ds = df.load(dataset::input<AnaQ::Tree>(tree_files, tree_name));

  auto n_jet = ds.read(dataset::column<unsigned int>("nJet"));
  auto jets_pt = ds.read(dataset::column<VecF>("Jet_pt"));
  auto jets_eta = ds.read(dataset::column<VecF>("Jet_eta"));
  auto jets_phi = ds.read(dataset::column<VecF>("Jet_phi"));
  auto jets_m = ds.read(dataset::column<VecF>("Jet_mass"));

  auto n_muon = ds.read(dataset::column<unsigned int>("nMuon"));
  auto mus_pt = ds.read(dataset::column<VecF>("Muon_pt"));
  auto mus_eta = ds.read(dataset::column<VecF>("Muon_eta"));
  auto mus_phi = ds.read(dataset::column<VecF>("Muon_phi"));

  auto n_elec = ds.read(dataset::column<unsigned int>("nElectron"));
  auto els_pt = ds.read(dataset::column<VecF>("Electron_pt"));
  auto els_eta = ds.read(dataset::column<VecF>("Electron_eta"));
  auto els_phi = ds.read(dataset::column<VecF>("Electron_phi"));

  auto jets_ptcut = df.define(
      column::expression([](VecF const &pts) { return pts > 30; }))(jets_pt);
  auto jets_mudr = df.define(column::definition<IsolatedJetSelection>(
      0.4, 10.0))(jets_eta, jets_phi, mus_pt, mus_eta, mus_phi);
  auto jets_eldr = df.define(column::definition<IsolatedJetSelection>(
      0.4, 10.0))(jets_eta, jets_phi, els_pt, els_eta, els_phi);
  auto goodjet_mask = jets_ptcut && jets_mudr && jets_eldr;
  auto goodjet_sumpt =
      df.define(column::expression([](VecF const &vec, VecI const &mask) {
        return Sum(vec[mask]);
      }))(jets_pt, goodjet_mask);

  auto cut_goodjet = df.filter(column::expression(
      [](VecI const &goodjet) { return Sum(goodjet); }))(goodjet_mask);

  auto h_sumpt_goodjet =
      df.get(query::output<AnaQ::Hist<1, float>>("goodjet_sumpt", 185, 15, 200))
          .fill(goodjet_sumpt)
          .at(cut_goodjet);

  TCanvas c;
  h_sumpt_goodjet->Draw();
  c.SaveAs("task_7.png");
}

int main(int argc, char **argv) {
  int nthreads = 0;
  if (argc == 2) {
    nthreads = strtol(argv[1], nullptr, 0);
  }
  auto tic = std::chrono::steady_clock::now();
  task(nthreads);
  auto toc = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = toc - tic;
  std::cout << "used threads = " << nthreads
            << ", elapsed time = " << elapsed_seconds.count() << "s"
            << std::endl;
}