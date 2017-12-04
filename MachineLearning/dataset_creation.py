#pisano u python 3
import random
import numpy as np

def create_dataset(hm,variance,step=2,correlation=False):  #ovo 2 i false su defaultne vrijednosti
    val = 1                                                #umjesto false moze ic 'pos' i 'neg' 
    ys = []                                       #hm je 'how many' tj koliko tocaka treba za set
    for i in range(hm):
        y = val + random.randrange(-variance,variance)   #na prijasnju vrijednost doda random br
        ys.append(y)
        if correlation and correlation == 'pos':
            val+=step                             #defaultni value je 1 a ako zelim korelaciju onda mjenjam uvjek defaultni value da mi globalno tocke idu u nekom pravcu gore ili dole, tj povecanje tog valuea mi odreduje golabni nagib tog snopa tocki , regularno su sve tocke izmedu +- varianca
        elif correlation and correlation == 'neg':
            val-=step

    xs = [i for i in range(len(ys))]      # punjenje x-eva moglo je i [i for i in range(hm)]
    
    return np.array(xs, dtype=np.float64),np.array(ys,dtype=np.float64)  #numpy ima svoje arraye kojiima treba odredit datatype
