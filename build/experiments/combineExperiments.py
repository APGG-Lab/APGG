import csv
import sys
import os
import numpy as np
import pandas as pd

def main():
    if len(sys.argv) != 2:
        print("Argument 1 missing")
        input()

    folderName = sys.argv[1]

    setup = np.load(folderName + "/setup.npy", allow_pickle=True).item()
    iters = setup["iternames"]

    fileList = getFilteredFileList(folderName, "score")
    data = combine(iters,fileList)
    saveFile(data, folderName)

def getFilteredFileList(folder, filter):
    fileList = []
    for root, directories, files in os.walk(folder):
        for file in files:
            if filter in file:
                fileList.append(folder + "/" + file)

    print("Found " + str(len(fileList)) + " " + filter + " files")
    return np.array(sorted(fileList))

def combine(iter, fileList):
    counter = 0
    iterCp = list(iter)
    fileListCp = list(fileList)
    data = []


    for iteration in iterCp:
        counter = 0
        single = []
        for file in fileListCp:
            if iteration in file:
                counter += 1
                if(counter==1):
                    df = pd.read_csv(file, header=0, sep = ";")[-1:]
                    dfDev = pd.read_csv(file, header=0, sep = ";")[-1:]
                else:
                    df = df.add(pd.read_csv(file, header=0, sep = ";")[-1:])
                    dfDev = pd.concat([dfDev, pd.read_csv(file, header=0, sep = ";")[-1:]])

        df['nCooperation'] = df['nCooperators'] + df['nMoralists']
        df['nPunishment'] = df['nMoralists'] + df['nImmoralists']
        df['nNoCooperation'] = df['nDefectors'] +  df['nImmoralists']
        df['nNoPunishment'] = df['nCooperators'] + df['nDefectors']

        dfDev['nCooperation'] = dfDev['nCooperators'] + dfDev['nMoralists']
        dfDev['nPunishment'] = dfDev['nMoralists'] + dfDev['nImmoralists']
        dfDev['nNoCooperation'] = dfDev['nDefectors'] +  dfDev['nImmoralists']
        dfDev['nNoPunishment'] = dfDev['nCooperators'] + dfDev['nDefectors']


        df = df.div(counter)

        dfTemp = pd.DataFrame()

        #Standard Deviation Calculations
        roles = ["nCooperators", "nDefectors", "nMoralists", "nImmoralists", "nCooperation", "nPunishment", "nNoCooperation", "nNoPunishment"]
        sampleSize = counter
        tempList = []
        for groups in df:
            if groups in roles:
                stdDev = np.std(dfDev[groups].values)
                stdErr = stdDev / np.sqrt(sampleSize)
                dfTemp[groups] = [stdErr]
                tempList.append(stdDev)
        dfTemp["generation"] = [float(df["generation"])]
        df = pd.concat([df, dfTemp])
        df["setup"] = iteration
        data.append(df)

    print(data)
    print(type(data[0]))
    return data

def saveFile(data, folder):
    counter = 0
    for comb in data:
        comb.reset_index(drop=True, inplace=True)
        comb.to_csv(str(folder) + "/combined_" + str(comb["setup"][0] + ".csv"))
        counter += 1
    print(str(counter) + " combined files saved to " + folder)
main()
