import csv


csvData = [
    ["numGenerations", "eliminationCount","groupSize",
     "width","height",
     "cooperateCost","synergyFactor",
     "punishmentCost","punishmentFine",
     "matchupType","selectorType","repopulationType","gridType","payoffType","mutatorType",
     "mutationRate",
     "showAllGenerations",
     "archiveData","visualize",
     "folderName","logSuffix","timeToFile","timeToFolder",
     "consoleOutExponent"]
]

baseEntry = {
    'numGenerations' :  450000,
    'eliminationCount' : 100,
    'groupSize' : 8,
    'width' : 32,
    'height' : 32,
    'cooperateCost' : 1,
    'synergyFactor' : 1,
    'punishmentcost' : 0.0,
    'punishmentfine' : 0.0,
    'matchuptype': 0, 'selectortype' : 1, 'repopulationtype' : 1, 'gridtype' : 0, 'payofftype' : 0, 'mutatortype' : 0,
    'mutationRate' : 0.01,
    'showallgenerations' : 0,
    'archiveData' : 1,
    'visualize' : 0,
    'folderName' : 'fig6-exp',
    'logSuffix': 'test1_r1',
    'timeToFile' : 1,
    'timeToFolder' : 0,
    'consoleOutExponent' : 10
}

i = 1.0
while i < 6.5:
    for j in range(0, 30):
        copy = baseEntry
        copy["synergyFactor"] = i
        copy["logSuffix"] = "exp" + str(j) + "-syn" + str(i)

        for k in range(0,2):
            copy["mutatortype"] = k
            copy['folderName'] = 'fig6-mut' + str(k) + "-zeroPunish"
            
            arrayLine = list(copy.values())
            csvData.append(arrayLine)
    i += 0.5

with open('configs.csv', 'w', newline='') as csvFile:
    writer = csv.writer(csvFile, delimiter=";", )
    writer.writerows(csvData)
csvFile.close()
