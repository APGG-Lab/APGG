import os
import sys
import csv
import matplotlib.pyplot as plt

num_experiments = 30;

def main():
    print("Test")
    score_fileList = getFilteredFileList('./', 'score')
    result = analyseScoreFiles(score_fileList)
    showScorePlot(result)


    lod_fileList = getFilteredFileList('./', 'LOD')
    result = analyseLODFiles(lod_fileList)
    showLODPlot(result)
    plt.show()

def getSynergyFactor(fileName):
    return (fileName[-10:])

def getFilteredFileList(folder, filter):
    fileList = []
    for root, directories, files in os.walk(folder):
        for file in files:
            if filter in file:
                fileList.append(file)

    return sorted(fileList, key = getSynergyFactor)

def analyseScoreFiles(fileList):
    i = 0;
    csvData = []
    types = {"c": 0, "d" : 0, "m" : 0, "i" : 0, 'np': 0, 'p': 0, 'coop': 0, 'nocoop' : 0}
    csvData.append(list(types.values()))
    while(i < len(fileList)):
        types = {"c": 0, "d" : 0, "m" : 0, "i" : 0, 'np': 0, 'p': 0, 'coop': 0, 'nocoop' : 0}
        for j in range(i, i+num_experiments):
            file = fileList[j]
            lastLine = getLastLineOfFileAsCSV(file)
            types["c"] += int(lastLine[1])
            types["d"] += int(lastLine[2])
            types["m"] += int(lastLine[3])
            types["i"] += int(lastLine[4])
        types["np"] = types["c"] + types["d"]
        types["p"] = types["m"] + types["i"]
        types["coop"] = types["c"] + types["m"]
        types["nocoop"] = types["d"] + types["i"]
        types["c"] /= num_experiments
        types["d"] /= num_experiments
        types["m"] /= num_experiments
        types["i"] /= num_experiments
        types["np"] /= num_experiments
        types["p"] /= num_experiments
        types["coop"] /= num_experiments
        types["nocoop"] /= num_experiments
        csvData.append(list(types.values()))

        print("Status: " + str(i));
        i+=30

    with open('../results.csv', 'a', newline='') as csvFile:
        writer = csv.writer(csvFile, delimiter=";")
        writer.writerows(csvData)
        csvFile.close()
    return csvData

def analyseLODFiles(fileList):
    i = 0;
    csvData = []
    types = {"c": 0, "d" : 0,}
    csvData.append(list(types.values()))
    while(i < len(fileList)):
        types = {"c": 0, "d" : 0}
        for j in range(i, i+num_experiments):
            file = fileList[j]
            lastLine = getLastLineOfFileAsCSV(file)
            types["c"] += float(lastLine[7])
            types["d"] += float(lastLine[8])
        types["c"] /= num_experiments
        types["d"] /= num_experiments
        csvData.append(list(types.values()))

        print("Status: " + str(i));
        i+=30

    with open('../results_LOD.csv', 'a', newline='') as csvFile:
        writer = csv.writer(csvFile, delimiter=";")
        writer.writerows(csvData)
        csvFile.close()
    return csvData

def showScorePlot(y):
    x = [1.0, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6]
    labels = ['cooperate', 'defect', 'moralist', 'immoralist', 'fracPun', 'fracNonPun', 'fracCoop', 'fracNoCoop']
    plt.figure(1)
    plt.xticks(x, x)
    plt.xlabel("R")
    plt.ylabel("Num Agents")
    plt.plot(x, y)
    # call method plt.legend
    plt.legend(labels)

def showLODPlot(y):
    x = [1.0, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6]
    labels = ['pCoop', 'pMoral']
    plt.figure(2)
    plt.xticks(x, x)
    plt.xlabel("R")
    plt.ylabel("Percent")
    plt.plot(x, y)
    # call method plt.legend
    plt.legend(labels)

def getLastLineOfFileAsCSV(file):
    fileHandle = open(os.path.join('./', file), "r")
    lineList = fileHandle.readlines()
    fileHandle.close()
    lastLine = lineList[len(lineList)-1];
    columns = lastLine.split(';')
    return columns

main()
