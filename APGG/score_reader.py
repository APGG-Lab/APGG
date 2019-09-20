import os
import sys
import matplotlib
import matplotlib.pyplot as plt

folder = "experiment1"

if len(sys.argv) > 1:
    folder = sys.argv[1]

fileList = []

for root, directories, files in os.walk(folder):
    for file in files:
        if 'score_' in file:
            fileList.append(file)

cooperators = []
defectors = []
moralists = []
immoralists = []

for file in fileList:
    print(file)
    fileHandle = open(os.path.join(root, file), "r")
    lineList = fileHandle.readlines()
    fileHandle.close

    lastLine = lineList[len(lineList)-1]
    print(lastLine)

    columns = lastLine.split(';')

    cooperators.append(int(columns[1]))
    defectors.append(int(columns[2]))
    moralists.append(int(columns[3]))
    immoralists.append(int(columns[4]))

print("Average number of cooperators: ", (sum(cooperators)/len(cooperators)))
print("Average number of defectors: ", (sum(defectors)/len(defectors)))
print("Average number of moralists: ", (sum(moralists)/len(moralists)))
print("Average number of immoralists: ", (sum(immoralists)/len(immoralists)))

plt.plot(fileList, cooperators, color='yellow')
plt.plot(fileList, defectors, color='purple')
plt.plot(fileList, moralists, color='green')
plt.plot(fileList, immoralists, color='red')

plt.title('Population of cooperators, defectors, moralists and immoralists')
plt.legend(['cooperators', 'defectors', 'moralists', 'immoralists'])
plt.xlabel('Result')
plt.xticks(rotation=45)
plt.ylabel('Number of Organims')
plt.show()