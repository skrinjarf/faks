import numpy as np
import warnings
from collections import Counter
#dont forget this
import pandas as pd
import random


def k_nearest_neighbors(data, predict, k=3): #fja iz MyKNNeighborsClassifier.py
    if len(data) >= k:   
        warnings.warn('K is set to a value less than total voting groups!')
    distances = []
    for group in data:
        for features in data[group]:
            euclidean_distance = np.linalg.norm(np.array(features)-np.array(predict))
            distances.append([euclidean_distance,group])
    votes = [i[1] for i in sorted(distances)[:k]]
    vote_result = Counter(votes).most_common(1)[0][0]
    return vote_result

df = pd.read_csv('breast_cancer_data')
df.replace('?',-99999, inplace=True)
df.drop(['id'], 1, inplace=True)
full_data = df.astype(float).values.tolist()  #eksplicitno baci sve u float jer su neki br u stringu i pretvori data u listu
#print full_data lijepo ispise sve, full data je primio sve

random.shuffle(full_data)  #promjesa data

test_size = 0.2*len(full_data)  #20% trebat ce mu kad bude koristio prvih 80% podataka za trening i 20 % za test
train_set = {2:[], 4:[]}
test_set = {2:[], 4:[]}   #kreira setove sa 2 klase u koje ce spremat rakove, 2 benigni 4 maligni
train_data = full_data[:-int(test_size)] # uzmi sve dok ne dodes do zadnjih 20 %
test_data = full_data[-int(test_size):] #uzmi zadnjih 20 posto nisam siguran ali mislim da ovaj - oznacava da se misli zadnji 20% bez doga bi bilo valjda dok ne dodes do 20 posto i od 20% do kraja 

#data je stvarno spremljen u test i train data


for i in train_data:
    train_set[i[-1]].append(i[:-1])  #pretpostavljam da -1 oznacava da on sam procjeni 


for i in test_data:
    test_set[i[-1]].append(i[:-1])
    

correct = 0
total = 0

for group in test_set:   #grupe su 2 i 4
    
    for data in test_set[group]:  #podatci iz svake grupe
      
        vote = k_nearest_neighbors(train_set, data, k=5)  #5 zato jer je to defaultni br za k u scikit-learn paketu 
        
        if (group == vote):  
	   correct += 1
           
        total += 1
        #nade dobar correct i total ali correct/total iz nekog razloga pise kao 0.0
print 'Accuracy:', correct/float(total)
