import pandas as pd
import matplotlib.pyplot as plt

def scatterDesign(axescolor:str, xlabel:str, ylabel:str, title:str, 
    titlecolor:str, plot=plt):
    plot.figure(figsize=(14,14), facecolor=axescolor)
    plot.xlabel(xlabel, fontweight='bold', fontsize=35)
    plot.ylabel(ylabel, fontweight='bold', fontsize=35)
    plot.title(title, fontweight='bold', fontsize=50)
    ax = plt.gca()
    ax.set_facecolor((0.06,0.06,0.06))
    ax.spines['bottom'].set_color('white')
    ax.spines['top'].set_color('white')
    ax.spines['left'].set_color('white')
    ax.spines['right'].set_color('white')
    ax.xaxis.label.set_color(titlecolor)
    ax.yaxis.label.set_color(titlecolor)
    ax.grid(alpha=0.1)
    ax.title.set_color('white')
    ax.tick_params(axis='x', colors='white')
    ax.tick_params(axis='y', colors='white')

    plot.xticks(fontsize=32)
    plot.yticks(fontsize=32)

def plotFromExcelFile(name:str):
    #constants
    axescolor:str = 'black'
    scattercolor:str = 'yellow'
    xlabel:str = 'R/a'
    ylabel:str = 'E/E1'
    titlecolor:str = 'white'
    title = 'E/E1 vs R/a'
    scatterDesign(axescolor=axescolor, xlabel=xlabel, ylabel=ylabel, title=title, 
    titlecolor=titlecolor)
    csv = pd.read_csv(name+'.csv')
    x: list[float] = csv['x'].values
    E: list[float] = csv['E'].values
    plt.plot(x[5:], E[5:], linewidth=5)
    plt.savefig(name+'.jpg')
    plt.show()

plotFromExcelFile('plot1')
#plotFromExcelFile('plot2')
