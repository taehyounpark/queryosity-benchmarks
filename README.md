# queryosity-benchmarks

## Buildling & reproducing results

```console
$ mkdir build && cd build/
$ cmake ../ & make -j4
$ source setup.sh
$ cd ../results/
$ task_<i> <num_threads>
```

## [IRIS HEP ADL benchmarks](https://github.com/iris-hep/adl-benchmarks-index/tree/master)

Input data file:
* [Converted to NanoAOD](https://github.com/cms-opendata-analyses/AOD2NanoAODOutreachTool) from [2012 CMS open data](http://opendata.cern.ch/record/6021):
  * root://eospublic.cern.ch//eos/root-eos/benchmark/Run2012B_SingleMu.root (16 GiB, 53 million events)

Tasks:
1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of all events.
1. Plot the <i>p</i><sub>T</sub> of all jets.
1. Plot the <i>p</i><sub>T</sub> of jets with |<i>η</i>| < 1.
1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of events that have at least two jets with <i>p</i><sub>T</sub> > 40 GeV.
1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of events that have an opposite-charge muon pair with an invariant mass between 60 and 120 GeV.
1. For events with at least three jets, plot the <i>p</i><sub>T</sub> of the trijet four-momentum that has the invariant mass closest to 172.5 GeV in each event and plot the maximum <i>b</i>-tagging discriminant value among the jets in this trijet.
1. Plot the scalar sum in each event of the <i>p</i><sub>T</sub> of jets with <i>p</i><sub>T</sub> > 30 GeV that are not within 0.4 in Δ<i>R</i> of any light lepton with <i>p</i><sub>T</sub> > 10 GeV.
1. For events with at least three light leptons and a same-flavor opposite-charge light lepton pair, find such a pair that has the invariant mass closest to 91.2 GeV in each event and plot the transverse mass of the system consisting of the missing tranverse momentum and the highest-<i>p</i><sub>T</sub> light lepton not in this pair.

## Performance (elapsed time [s])

Hardware:
- CPU: 2 x Intel E5-2683 v4 Broadwell @ 2.1Ghz
- I/O: SSD

| Threads         | Task 1 | Task 2 | Task 3 | Task 4 | Task 5 |  Task 6 | Task 7 | Task 8 |
| :---            | ---:   | ---:   | ---:   | ---:   | ---:   | ---:    |  ---:  | ---:   |
| 1 thread        |  33.76 |  87.01 | 124.05 | 125.84 | 155.33 | 1982.39 | 502.87 |        |
| 2 threads       |  17.43 |  50.05 |  66.95 |  57.16 |  84.30 |         | 230.66 |        |
| 10 threads      |   4.41 |   9.63 |  22.34 |  12.19 |  16.91 |  150.96 |  50.58 |  34.91 |
