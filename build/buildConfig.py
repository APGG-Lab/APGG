import csv
import itertools
import numpy
import os

def main():
    num_experiments = 100 #How often do you want to repeat the experiment
    baseEntry = {
        'numGenerations' :  100000,
        'eliminationCount' : 100,
        'groupSize' : 5,
        'width' : 100,
        'height' : 10,
        'cooperateCost' : 1.0,
        'synergyFactor' : 3.0,
        'punishmentCost' : 0.2,
        'punishmentFine' : 0.8,
        'gridType' : Grid['Default'],
        'payoffType' : PayoffCalculator['Group'],
        'payoffIndividualism' : 1.0,
        'selectorType' : Selector['Random'],
        'repopulationType' : Repopulator['Proportionate'],
        'mutatorType' : Mutator['Random'],
        'mutationRate' : 0.02,
        'folderName' : 'test',
        'logSuffix': 'test1_',
        'timeToFile' : 1,
        'timeToFolder' : 0
    }

    addIteration('synergyFactor', 1.5, 7.0, 0.125) #From, To, StepSize

    buildConfig("configs.csv", num_experiments, baseEntry)

    simpleConfig(baseEntry)

#=======================================================

Grid = {'Default': 0, 'Spatial' : 1}
PayoffCalculator = {'Default' : 0, 'Group': 1, 'Asymmetric': 2 }
Selector = {'Elite' : 0, 'Random' : 1}
Mutator = {'Random' : 0, 'RandomThreshold': 1}
Repopulator = { 'Random' : 0, 'Proportionate' : 1, 'Spatial' : 2}

iterations = []
iterationValues = []

def addIteration(index, startVal, endVal, stepSize):
    """Adds iteration to array of iterations"""

    iteration =  {'key': index, 'from' : startVal, 'to' : endVal, 'stepSize' : stepSize}
    iterations.append(iteration)
    return iteration


def buildConfig(configName, num_experiments, baseEntry):
    """Generates a config and writes it to configName"""

    csvData = [] #CSV-Data Array
    num_experiments_counter = 0

    #trailing semicolon fix for linux
    temp = list(baseEntry.keys())
    temp.append("")
    csvData.append(temp)
    recursiveIteration(0, baseEntry.copy(), csvData, num_experiments)

    writeConfig(configName, csvData)
    print("Wrote " + str(len(csvData)) + " experiments to \"" + configName + "\"")


def recursiveIteration(iterationIndex, baseEntry, csvData, num_experiments):
    """Generates experiments recursively"""
    if iterationIndex >= len(iterations): #reached end of iterations
        for i in range(num_experiments):
            experimentCopy = baseEntry.copy()

            if experimentCopy["logSuffix"] not in iterationValues:
                iterationValues.append(experimentCopy["logSuffix"])

            experimentCopy['logSuffix'] += "-exp" + str(i)
            csvData.append(list(experimentCopy.values()))
            print(experimentCopy['logSuffix'])
        return

    iteration = iterations[iterationIndex]

    counter = iteration['from']
    while counter <= iteration['to']:
        baseCopy = baseEntry.copy()
        baseCopy[iteration['key']] = counter
        baseCopy['logSuffix'] += "-" + iteration['key'] + str(counter)
        counter += iteration['stepSize']
        recursiveIteration(iterationIndex +1, baseCopy, csvData, num_experiments)

def writeConfig(name, data):
    """Writes csv to filesystem"""

    with open(name, 'w', newline='') as csvFile:
        writer = csv.writer(csvFile, delimiter=";", )
        writer.writerows(data)
        csvFile.close()

def simpleConfig(base):
    baseConf = dict(base)
    for i, iter in enumerate(iterationValues):
        iterationValues[i] = iter.replace(baseConf["logSuffix"]+"-", "")
    baseConf["iternames"] = iterationValues
    baseConf["iters"] = iterations
    if not(os.path.exists("./experiments/" + baseConf["folderName"])):
        os.mkdir("./experiments/" + baseConf["folderName"])
    numpy.save("./experiments/" + baseConf["folderName"] + "/setup.npy", baseConf)
    print(baseConf)

#Neat trick to define methods AFTER using them
if __name__ == '__main__':
    main()
