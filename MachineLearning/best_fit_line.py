# kod je pisan u python3

from statistics import mean  #mean je prosjek
import numpy as np           #numpy ima ogroman library za racun sa matricama
import random                #za kreiranje dataset-a
import matplotlib.pyplot as plt          #za plot
from matplotlib import style
style.use('ggplot')      #ggplot je jedan od ljepih stilova za plotanje


def create_dataset(hm,variance,step=2,correlation=False):      #objasnjenje u dataset_creation.py
    val = 1
    ys = []
    for i in range(hm):
        y = val + random.randrange(-variance,variance)
        ys.append(y)
        if correlation and correlation == 'pos':
            val+=step
        elif correlation and correlation == 'neg':
            val-=step

    xs = [i for i in range(len(ys))]
    
    return np.array(xs, dtype=np.float64),np.array(ys,dtype=np.float64)

#xs = np.array([1,2,3,4,5], dtype=np.float64) 
#ys = np.array([5,4,6,5,6], dtype=np.float64)
#NETREBA AKO KORISTIM CREATE_DATASET

def best_fit_slope_and_intercept(xs,ys):      # y=mx+b    
    m = (((mean(xs)*mean(ys)) - mean(xs*ys)) /
         ((mean(xs)*mean(xs)) - mean(xs*xs)))
    
     b = mean(ys) - m*mean(xs)       #formula
     
    return m,b                #postoji gotova formula za nagib best_fit_linea

def squared_error(ys_orig,ys_line):
    return sum((ys_line - ys_orig) * (ys_line - ys_orig))

def coefficient_of_determination(ys_orig,ys_line):
    y_mean_line = [mean(ys_orig) for y in ys_orig]
    squared_error_regr = squared_error(ys_orig, ys_line)
    squared_error_y_mean = squared_error(ys_orig, y_mean_line)
    return 1 - (squared_error_regr/squared_error_y_mean)  #formula


xs, ys = create_dataset(40,40,2,correlation='pos') #u xy i ys napunimo krenirane podatke
m, b = best_fit_slope_and_intercept(xs,ys)
print(m,b) 

regression_line = [(m*x)+b for x in xs] 
##gornja linija je ekvivalentna sa 
##regression_line = []
##for x in xs:
##      regression_line.append((m*x)+b)

r_squared = coefficient_of_determination(ys,regression_line)
print(r_squared)

plt.scatter(xs,ys,color='#003F72',label='data')
plt.plot(xs, regression_line, label='regression line')
plt.legend(loc=4)
plt.show()

# ovo zadnje je kod za plotanje ali treba 
# import matplotlib.pyplot as plt
# from matplotlib import style i moze se dodati style.use('ggplot') za lijepi izgled