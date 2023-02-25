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

    print(df)
    print(df['nMoralists'][0])

    dfValues = pd.DataFrame()
    dfErrors = pd.DataFrame()

    print("df\n", df, df.shape)

    dfValues = df.iloc[0::2,:].copy()
    dfErrors = df.iloc[1::2,:].copy()
    print("dfValues\n", dfValues, dfValues.shape)
    print("dfErrors\n",  dfErrors,  dfErrors.shape)

    dfValues.reset_index(drop=True, inplace=True)
    generations = dfValues["generation"] + 1


    for i, row in dfValues.iterrows():
        if(searchString in row["setup"]):
            dfValues.at[i, "setup"] = row["setup"].strip(searchString).strip('-').strip(iterToPlotName)

    for i, row in dfErrors.iterrows():
        if(searchString in row["setup"]):
            dfErrors.at[i, "setup"] = row["setup"].strip(searchString).strip('-').strip(iterToPlotName)


    dfValues = dfValues.sort_values('setup')
    dfErrors = dfErrors.sort_values('setup')

    print("dfValues\n", dfValues, dfValues.shape)
    print("dfErrors\n",  dfErrors,  dfErrors.shape)


    nCooperation = []
    nPunishment = []
    nNoCooperation = []
    nNoPunishment = []
    nCooperators = []
    nDefectors = []
    nMoralists = []
    nImmoralists = []
    x = []

    for i, row in dfValues.iterrows():
        x.append(float(dfValues.at[i, "setup"]))
        nCooperation.append(float(dfValues.at[i, "nCooperation"]))
        nPunishment.append(float(dfValues.at[i, "nPunishment"]))
        nNoCooperation.append(float(dfValues.at[i, "nNoCooperation"]))
        nNoPunishment.append(float(dfValues.at[i, "nNoPunishment"]))
        nCooperators.append(float(dfValues.at[i, "nCooperators"]))
        nDefectors.append(float(dfValues.at[i, "nDefectors"]))
        nMoralists.append(float(dfValues.at[i, "nMoralists"]))
        nImmoralists.append(float(dfValues.at[i, "nImmoralists"]))

    nCooperationError = []
    nPunishmentError = []
    nNoCooperationError = []
    nNoPunishmentError = []
    nCooperatorsError = []
    nDefectorsError = []
    nMoralistsError = []
    nImmoralistsError = []

    for i, row in dfErrors.iterrows():
        nCooperationError.append(float(dfErrors.at[i, "nCooperation"]))
        nPunishmentError.append(float(dfErrors.at[i, "nPunishment"]))
        nNoCooperationError.append(float(dfErrors.at[i, "nNoCooperation"]))
        nNoPunishmentError.append(float(dfErrors.at[i, "nNoPunishment"]))
        nCooperatorsError.append(float(dfErrors.at[i, "nCooperators"]))
        nDefectorsError.append(float(dfErrors.at[i, "nDefectors"]))
        nMoralistsError.append(float(dfErrors.at[i, "nMoralists"]))
        nImmoralistsError.append(float(dfErrors.at[i, "nImmoralists"]))


    xi = []
    for i in range(len(x)):
        xi.append(i+1)

    myListCoop = [x/1000 for x in nCooperation]
    myListPunish = [x/1000 for x in nPunishment]
    myListCoopError = [x/1000 for x in nCooperationError]
    myListPunishError = [x/1000 for x in nPunishmentError]

    combCoopPos = np.array(myListCoop) + np.array(myListCoopError)
    combCoopNeg = np.array(myListCoop) - np.array(myListCoopError)
    combPunishPos = np.array(myListPunish) + np.array(myListPunishError)
    combPunishNeg = np.array(myListPunish) - np.array(myListPunishError)

    plt.figure(1)
    plt.xticks(xi, x)
    plt.xticks(rotation=90)
    plt.xlabel(iterToPlotName)
    plt.ylabel(r"$P_C$")
    plt.ylim(0,1)
    plt.twinx()
    plt.ylim(0,1)
    plt.ylabel(r"$P_P$")
    plt.fill_between(range(len(myListCoop)), combCoopPos, combCoopNeg, alpha = 0.3, color = "k")
    plt.fill_between(range(len(myListPunish)), combPunishPos, combPunishNeg, alpha = 0.3, color = "r")
    plt.plot(myListCoop, label="Cooperators", color="black")
    plt.plot(myListPunish, label="Punishers", color="red")
    #plt.plot(nNoCooperation, label="nNoCooperation")
    #plt.plot(nNoPunishment, label="nNoPunishment")
    #plt.plot(nCooperators, label="nCooperators")
    #plt.plot(nDefectors, label="nDefectors")
    #plt.plot(nMoralists, label="nMoralists")
    #plt.plot(nImmoralists, label="nImmoralists")


    # call method plt.legend
    plt.legend()
    plt.show()


main()
