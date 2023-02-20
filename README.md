# APGG (Asymetric Public Goods Games)

![Logo](https://mirko.dev/apgg_logo_full.png)

Code for asymetric public goods games

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
