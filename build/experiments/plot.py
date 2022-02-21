import os
import sys
import csv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#number of experiments
num_experiments = 10;

def main():
    if len(sys.argv) != 2:
        print("Argument 1 missing")
        input()

    folderName = sys.argv[1]

   # print("Test")
    setup = np.load(folderName + "/setup.npy", allow_pickle=True).item()
    iters = setup["iters"]

    print("\nWhich iterations do you want to plot?\n")
    for i, iter in enumerate(iters):
        print("ID: " + str(i), iter)
        iters[i]["ID"] = i

    iterToPlot = int(input("\nInput the ID of the iterations that you want to plot: "))
    iterToPlotName = ""
    remainingIters = list(iters)



    for i, iter in enumerate(remainingIters):
        if(iter["ID"]==iterToPlot):
            iterToPlotName = iter["key"]
            remainingIters.pop(i)

    if(len(remainingIters) != 0):
        print("\nWhat fix value do you want to use for the remaining Iterations?")
        for i, iter in enumerate(remainingIters):
            print(iter)
            remainingIters[i]["default"] = float(input("Input value for above mentioned iteration: "))

    searchString = ""
    for i, iter in enumerate(remainingIters):
        if(i!=0):
            searchString += "-" + str(iter["key"]) + str(iter["default"])
        else:
            searchString += str(iter["key"]) + str(iter["default"])


    fileList = []
    for root, directories, files in os.walk(folderName):
        for file in files:
            if "combined" in file and searchString in file:
                fileList.append(folderName + "/" + file)

    for i, file in enumerate(fileList):
        if(i==0):
            df = pd.read_csv(file, index_col=0, header=0, sep = ",")
        else:
            df = df.append(pd.read_csv(file, index_col=0, header=0, sep = ","))

    df.reset_index(drop=True, inplace=True)
    generations = df["generation"] + 1
    df['nCooperation'] = df['nCooperators'] + df['nMoralists']
    df['nPunishment'] = df['nMoralists'] + df['nImmoralists']
    df['nNoCooperation'] = df['nDefectors'] +  df['nImmoralists']
    df['nNoPunishment'] = df['nCooperators'] + df['nDefectors']


    for i, row in df.iterrows():
        if(searchString in row["setup"]):
            df.at[i, "setup"] = row["setup"].strip(searchString).strip('-').strip(iterToPlotName)

    df = df.sort_values('setup')


    nCooperation = []
    nPunishment = []
    nNoCooperation = []
    nNoPunishment = []
    nCooperators = []
    nDefectors = []
    nMoralists = []
    nImmoralists = []
    x = []

    for i, row in df.iterrows():
        x.append(float(df.at[i, "setup"]))
        nCooperation.append(float(df.at[i, "nCooperation"]))
        nPunishment.append(float(df.at[i, "nPunishment"]))
        nNoCooperation.append(float(df.at[i, "nNoCooperation"]))
        nNoPunishment.append(float(df.at[i, "nNoPunishment"]))
        nCooperators.append(float(df.at[i, "nCooperators"]))
        nDefectors.append(float(df.at[i, "nDefectors"]))
        nMoralists.append(float(df.at[i, "nMoralists"]))
        nImmoralists.append(float(df.at[i, "nImmoralists"]))

    xi = []
    for i in range(len(x)):
        xi.append(i+1)

    plt.figure(1)
    plt.xticks(xi, x)
    plt.xlabel(iterToPlotName)
    plt.ylabel("Num Agents")
    plt.plot(nCooperation, marker="o", label="nCooperation")
    plt.plot(nPunishment, marker="o", label="nPunishment")
    plt.plot(nNoCooperation, marker="o", label="nNoCooperation")
    plt.plot(nNoPunishment, marker="o", label="nNoPunishment")
    plt.plot(nCooperators, marker="o", label="nCooperators")
    plt.plot(nDefectors, marker="o", label="nDefectors")
    plt.plot(nMoralists, marker="o", label="nMoralists")
    plt.plot(nImmoralists, marker="o", label="nImmoralists")

    # call method plt.legend
    plt.legend()
    plt.show()


main()
