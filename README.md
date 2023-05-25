# ana-benchmarks

## Benchmark Tasks

1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of all events.
1. Plot the <i>p</i><sub>T</sub> of all jets.
1. Plot the <i>p</i><sub>T</sub> of jets with |<i>η</i>| < 1.
1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of events that have at least two jets with <i>p</i><sub>T</sub> > 40 GeV.
1. Plot the <i>E</i><sub>T</sub><sup>miss</sup> of events that have an opposite-charge muon pair with an invariant mass between 60 and 120 GeV.
1. For events with at least three jets, plot the <i>p</i><sub>T</sub> of the trijet four-momentum that has the invariant mass closest to 172.5 GeV in each event and plot the maximum <i>b</i>-tagging discriminant value among the jets in this trijet.
1. Plot the scalar sum in each event of the <i>p</i><sub>T</sub> of jets with <i>p</i><sub>T</sub> > 30 GeV that are not within 0.4 in Δ<i>R</i> of any light lepton with <i>p</i><sub>T</sub> > 10 GeV.
1. For events with at least three light leptons and a same-flavor opposite-charge light lepton pair, find such a pair that has the invariant mass closest to 91.2 GeV in each event and plot the transverse mass of the system consisting of the missing tranverse momentum and the highest-<i>p</i><sub>T</sub> light lepton not in this pair.

## Task Performance (elapsed time [s])

| Threads         | Task 1 | Task 2 | Task 3 | Task 4 | Task 5 | Task 6 | Task 7 | Task 8 |
| ---             | ---:   | ---:   | ---:   |  ---:  | ---:   | ---:   |  ---:  | ---:   |
| single-threaded |  44.74 |  87.01 |        |        |        |        |        |        |
| 2 threads       |  24.45 |  50.05 |        |        |        |        |        |        |
| 10 threads      |   5.77 |   9.63 |  30.82 |  14.52 |  31.33 | 176.05 |        |        |