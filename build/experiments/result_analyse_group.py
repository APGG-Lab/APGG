
def showScorePlot(y):
    x = [0, 1.0, 2, 3,4, 5, 6]
    labels = ['cooperate', 'defect', 'moralist', 'immoralist', 'fracPun', 'fracNonPun', 'fracCoop', 'fracNoCoop']
    plt.figure(1)
    plt.xticks(x, x)
    plt.xlabel("R")
    plt.ylabel("Num Agents")
    plt.plot(x, y)
    # call method plt.legend
    plt.legend(labels)

def showLODPlot2(y):
    col = 0
    row = 3
    print((y))
    arr = np.array(y)
    yArray = np.hsplit(arr, 2)

    print(yArray[0])

    x_range = np.arange(3.0,6.0,0.2)
    y_range = np.arange(0,1.1, 0.1)

    x_len = len(x_range)
    y_len = len(y_range)

    arrayCooperation = np.reshape(yArray[0], (x_len, y_len))
    arrayCooperation = np.swapaxes(arrayCooperation, 0,1)
    arrayMoral = np.reshape(yArray[1], (x_len, y_len))
    arrayMoral = np.swapaxes(arrayMoral, 0,1)

    print("=========")
    print(arrayCooperation)


    fig, axs = plt.subplots(1,2)
    cm = ['gray', 'gray']

    #plt.xticks(np.arange(0,25,5), [0,25,50,75,100])

    ax = axs[0]
    pcm = ax.pcolormesh(x_range, y_range, arrayCooperation, cmap=cm[0], vmin=0, vmax=1)
    fig.colorbar(pcm, ax=ax)


    ax = axs[1]
    pcm = ax.pcolormesh(x_range, y_range, arrayMoral, cmap=cm[1], vmin=0, vmax=1)
    fig.colorbar(pcm, ax=ax)

    plt.show()




import os
import sys 
import csv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#number of experiments
num_experiments = 50;

def main():
    if len(sys.argv) != 2:
        print("Argument 1 missing")
        input()

    folderName = sys.argv[1]

   # print("Test")
    score_fileList = getFilteredFileList(folderName, 'score')
    df_array = getDataframeArray(score_fileList)
    result_moral, result_cooperation = analyseScore(df_array)
    showScorePlot(result_moral, result_cooperation)

    plt.show()



#Extracts a key from a file for sorting (e.g. synergyfactor)
#This part shouldn't be relevant, if you have files which will use the
#following schema : [score|LOD]_prefix-key1-key2_exp0_timestamp.csv
def getSortingKey(fileName):
    return fileName #(fileName[-10:])

def getFilteredFileList(folder, filter):
    fileList = []
    for root, directories, files in os.walk(folder):
        for file in files:
            if filter in file:
                fileList.append(folder + "/" + file)

    print("Found " + str(len(fileList)) + " " + filter + " files")
    return np.array(sorted(fileList, key = getSortingKey))

def getDataframeArray(fileList):
    i = 0;
    k = 0; #chunk counter for logprints
    num_chunks = len(fileList)/num_experiments;
    df_collection = []

    print("\tSplitting files in " + str(num_chunks) + " chunks a " + str(num_experiments) + " files")


    while(i < len(fileList)):
        df_collection_chunk = []
        for j in range(i, i+num_experiments):
            df = getLastLineOfCSV(fileList[j])
            df_collection_chunk.append(df)

        df_result = pd.concat(df_collection_chunk) #collection which holds num_experiments rows
        df_collection.append(df_result) #array which holds combined data_frames

        i+=num_experiments
        k+=1
        print("\tGenerate dataframes for chunk " + str(k) + " of " + str(num_chunks))

    return df_collection

def analyseScore(df_array):    
    avgDFs = []

    print("\tConvert dataframes and generate AVG values");

    for df in df_array:
        #create meta columns
        df['nCooperation'] = df['nCooperators'] + df['nMoralists']
        df['nPunishment'] = df['nMoralists'] + df['nImmoralists']
        #df['nNoCooperation'] = df['nDefectors'] +  df['nImmoralists']
        #df['nNoPunishment'] = df['nCooperators'] + df['nDefectors']

        df = df.drop(columns=['generation', 'nCooperators', 'nMoralists', 'nImmoralists', 'nDefectors']) #Drop generation

        avgDF = round(df.mean())
        avgDFs.append(avgDF)

    df_result = pd.concat(avgDFs, axis=1).transpose() / 1000

    x_range = np.arange(3.0,6.0,0.2)
    y_range = np.arange(0,1.1, 0.1)

    x_len = len(x_range)
    y_len = len(y_range)

    npMoral = np.reshape(df_result['nPunishment'].to_numpy(), (x_len, y_len))
    npCooperation = np.reshape(df_result['nCooperation'].to_numpy(), (x_len, y_len))
    
    npMoral = np.swapaxes(npMoral, 0,1)
    npCooperation = np.swapaxes(npCooperation, 0,1)


    return npMoral,npCooperation


def showScorePlot(npMoral, npCooperation):
    x_range = np.arange(3.0,6.0,0.2)
    y_range = np.arange(0,1.1, 0.1)

    fig, axs = plt.subplots(1,2)
    cm = ['gray', 'gray']

    #plt.xticks(np.arange(0,25,5), [0,25,50,75,100])

    ax = axs[0]
    pcm = ax.pcolormesh(x_range, y_range, npCooperation, cmap=cm[0], vmin=0, vmax=1)
    fig.colorbar(pcm, ax=ax)


    ax = axs[1]
    pcm = ax.pcolormesh(x_range, y_range, npMoral, cmap=cm[1], vmin=0, vmax=1)
    fig.colorbar(pcm, ax=ax)

    plt.show()



def getLastLineOfCSV(file):
    df = pd.read_csv(file, header=0, sep = ";")
    return df[-1:]

main()
