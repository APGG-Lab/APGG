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
                else:
                    df = df.add(pd.read_csv(file, header=0, sep = ";")[-1:])
        df = df.div(counter)
        df["setup"] = iteration
        data.append(df)

    return data

def saveFile(data, folder):
    counter = 0
    for comb in data:
        comb.reset_index(drop=True, inplace=True)
        comb.to_csv(str(folder) + "/combined_" + str(comb["setup"][0] + ".csv"))
        counter += 1
    print(str(counter) + " combined files saved to " + folder)
main()
