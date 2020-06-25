import csv

def main():
    num_experiments = 10 #How often do you want to repeat the experiment
    baseEntry = {
        'numGenerations' :  100000,
        'eliminationCount' : 100,
        'groupSize' : 5,
        'width' : 40,
        'height' : 25,
        'cooperateCost' : 1.0,
        'synergyFactor' : 3.0,
        'punishmentCost' : 0.2,
        'punishmentFine' : 0.8,
        'gridType' : Grid['Default'],
        'payoffType' : PayoffCalculator['Group'],
        'payoffIndividualism' : 0.5,
        'selectorType' : Selector['Random'],
        'repopulationType' : Repopulator['Proportionate'],
        'mutatorType' : Mutator['Random'],
        'mutationRate' : 0.01,
        'folderName' : 'individualism-exp',
        'logSuffix': 'test1_',
        'timeToFile' : 1,
        'timeToFolder' : 0
    }

    addIteration('synergyFactor', 3.0, 6.0, 0.5) #From, To, StepSize
    addIteration('payoffIndividualism', 0.0, 1.0, 0.2) #From, To, StepSize

    buildConfig("configs.csv", num_experiments, baseEntry)

#=======================================================

Grid = {'Default': 0, 'Spatial' : 1}
PayoffCalculator = {'Default' : 0, 'Group': 1, 'Asymmetric': 2 }
Selector = {'Elite' : 0, 'Random' : 1}
Mutator = {'Random' : 0, 'RandomThreshold': 1}
Repopulator = { 'Random' : 0, 'Proportionate' : 1, 'Spatial' : 2}


def addIteration(index, startVal, endVal, stepSize):
    """Adds iteration to array of iterations"""

    iteration =  {'key': index, 'from' : startVal, 'to' : endVal, 'stepSize' : stepSize}
    iterations.append(iteration)
    return iteration

iterations = []

def buildConfig(configName, num_experiments, baseEntry):
    """Generates a config and writes it to configName"""

    csvData = [] #CSV-Data Array
    num_experiments_counter = 0

    csvData.append(list(baseEntry.keys()))
    recursiveIteration(0, baseEntry.copy(), csvData, num_experiments)

    writeConfig(configName, csvData)
    print("Wrote " + str(len(csvData)) + " experiments to \"" + configName + "\"")

def recursiveIteration(iterationIndex, baseEntry, csvData, num_experiments):
    """Generates experiments recursively"""

    if iterationIndex >= len(iterations): #reached end of iterations
        for i in range(num_experiments):
            experimentCopy = baseEntry.copy()
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

#Neat trick to define methods AFTER using them
if __name__ == '__main__':
    main()
