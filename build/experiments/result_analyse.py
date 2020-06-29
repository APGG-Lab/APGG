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
    score_fileList = getFilteredFileList(folderName, 'score')
    df_array = getDataframeArray(score_fileList)
    result_df = analyseScore(df_array)
    showScorePlot(result_df)

    lod_fileList = getFilteredFileList(folderName, 'LOD')
    df_array = getDataframeArray(lod_fileList)
    result_df = analyseLOD(df_array)
    showLODPlot(result_df)

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
        df = df.drop(columns=['generation']) #Drop generation

        #create meta columns
        df['nCooperation'] = df['nCooperators'] + df['nMoralists']
        df['nPunishment'] = df['nMoralists'] + df['nImmoralists']
        df['nNoCooperation'] = df['nDefectors'] +  df['nImmoralists']
        df['nNoPunishment'] = df['nCooperators'] + df['nDefectors']

        avgDF = round(df.mean())
        avgDFs.append(avgDF)

    df_result = pd.concat(avgDFs, axis=1).transpose()
    return df_result

def analyseLOD(df_array):
    avgDFs = []

    print("\tConvert dataframes and generate AVG values");

    for df in df_array:
        
        df = df.drop(columns=['payoff', 'faction', 'cooperated', 'moralist','nChildren']) #Drop unused values

        avgDF = df.mean()
        avgDFs.append(avgDF)

    df_result = pd.concat(avgDFs, axis=1).transpose()
    return df_result

def showScorePlot(df):
    x = [1, 2, 3, 4, 5, 6]
    labels = df.columns.values
    plt.figure(1)
    plt.xticks(x, x)
    plt.xlabel("R")
    plt.ylabel("Num Agents")
    plt.plot(x, df)
    # call method plt.legend
    plt.legend(labels)

def showLODPlot(df):
    x = [1, 2, 3, 4, 5, 6]
    labels = df.columns.values
    plt.figure(2)
    plt.xticks(x, x)
    plt.xlabel("R")
    plt.ylabel("Percent")
    plt.plot(x, df)
    # call method plt.legend
    plt.legend(labels)


def getLastLineOfCSV(file):
    df = pd.read_csv(file, header=0, sep = ";")
    return df[-1:]

main()
