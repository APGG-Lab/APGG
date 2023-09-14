# APGG (Asymetric Public Goods Games) [![DOI](https://joss.theoj.org/papers/10.21105/joss.04944/status.svg)](https://doi.org/10.21105/joss.04944)

![Logo](https://mirko.dev/apgg_logo_full.png)

APGG is a Framework that allows users to run, simulate and analyze Public Goods Games Experiments. APPG is written in a way that should allow users of all levels of experience to use, utalize and modify the Framework as desired.


## Installation
* Download the release from the [Release section ](https://github.com/APGG-Lab/APGG/tags)
* Extract the .zip archive

## Installation from Source

* C++17 or higher required!
* Clone the repository `git clone https://ips.hs-kempten.de/asymmetric-public-goods/apgg.git`
* Open the .sln project
* Compile the "Release" Version

For more information, please refer to our [Wiki page.](https://github.com/APGG-Lab/APGG/wiki/Build-From-Scratch)

## Getting started
1. Adjust the values in the main function of buildConfig.py to whatever values are suitable for your experiment (see Config Setup or [Wiki entry](https://github.com/APGG-Lab/APGG/wiki/ConfigValues)). By adding addIteration calls you can specify entire ranges of values for a config value that the script writes for you automatically. With multiple calls to this function every possible permutation of all values ranges is written. All these experiment setups will be run in sequence.
2. Run the buildConfig.py to generate the config.csv.
3. Run the executable.
4. After the conclusion of the experiments in order to visualize the data first run combineExperiments.py on the generated folder.
5. Run plot.py to get a chart of your data. Adjust as needed.

## Config Setup

For more information on this topic, please refer to our Wiki pages on [Config Values](https://github.com/APGG-Lab/APGG/wiki/ConfigValues) and [CSV Batch Experiements](https://github.com/APGG-Lab/APGG/wiki/CSV-Batch-Experiments).

| Config Key | Type (Limits) | Definition |
| -------- | -------- | -------- |
| numGenerations | int | Number of generations |
| eliminationCount |  int | Number of Organisms which will be eliminated every generation |
|groupSize | int |   Size of the group to play the Public Goods game |
|width | int | Theoretical grid width. Spatial isn't implemented atm, so just assume size = width * height |
|height | int | Theoretical grid height. Spatial isn't implemented atm, so just assume size = width * height |
|cooperateCost| int | Cost for Cooperation |
|synergyFactor| int | Synergy Multiplication factor for cooperation |
|punishmentCost| int | BaseCost for moralists/immoralists  s.o |
|punishmentFine | int | BaseFine for defectors / immporalists |
|matchupType | int | unused |
|selectorType| int  (0-1) |  0 = EliteSelector / 1 = RandomSelector (recommended by Dr. Hintze) |
|repopulatorType | int  (0-1) | 0 = RandomPopulator / 1 = ProportionateRepopulator (recommended by Dr. Hintze) |
|gridType | int  (0-1) | 0 = DefaultGrid |
|payoffType | int  (0-1) | 0 = DefaultPayoffGenerator |
|mutatorType | int  (0-1) | 0 = RandomMutator / 1 = ThresholdMutator (recommended by Dr. Hintze) |
|mutationRate | int  (0-100) | Mutationrate. 0 = no Mutation, 100 = every Organism will mutate every round |
|showAllGenerations | int  (0-1)  | Log all generations to std. out |
|archiveData | int  (0-1) | Archive data to csv |
|visualize | int (0-1) | Open python3 script after experiment (unused) |
|folderName| string  | name of the experiment
|logSuffix | string | Suffix for the experiment .csv file |
|timeToFile | int  (0-1) | Add timestamp to file |
|timeToFolder | int (0-1) | Add timestamp to folder |
|consoleOutExponent | int  | Multiplicator for interval output |

## Help
Visit our [Wiki](https://github.com/APGG-Lab/APGG/wiki) for a more in depth documentation

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Citation

Plaintext
```
Rosenthal et al., (2023). APGG - A Modular C++ Framework for Asymmetric Public Goods Games. Journal of Open Source Software, 8(89), 4944, https://doi.org/10.21105/joss.04944
```

Bibtex
```Bibtex
@article{Rosenthal2023, doi = {10.21105/joss.04944},
  url = {https://doi.org/10.21105/joss.04944},
  year = {2023},
  publisher = {The Open Journal},
  volume = {8}, number = {89},
  pages = {4944},
  author = {Mirko Rosenthal and David J. Richter and Falk Hübner and Jochen Staudacher and Arend Hintze},
  title = {APGG - A Modular C++ Framework for Asymmetric Public Goods Games},
  journal = {Journal of Open Source Software}
}
```
