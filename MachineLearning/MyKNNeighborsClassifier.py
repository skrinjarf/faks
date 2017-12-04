import numpy as np
import matplotlib.pyplot as plt
from matplotlib import style
import warnings            #to cisto pazi da je kolicina podataka uredu i da sve ima smisla logickog
from math import sqrt      #obicni korjen, kasnije ce biti i bolji nacin
from collections import Counter  #to ce nam brojat udaljenosti i glasove i ljepo
style.use('fivethirtyeight')     #stil plotanja

def k_nearest_neighbors(data, predict, k=3):  
    if len(data) >= k:        #ako zelimo usporedit sa vise brojeva nego sta ih ima, javi gresku
        warnings.warn('K is set to a value less than total voting groups!')
        
    distances = []    #radimo 2d listu u koju stavljamo liste sheme (udaljenost,grupa) pa onda sortiramo po udaljenosti
    for group in data:
        for features in data[group]:
            euclidean_distance = sqrt( (features[0]-predict[0])**2 + (features[1]-predict[1])**2 )
            distances.append([euclidean_distance,group]) #ovaj nacin je basic ali najsporiji
            
            #euclidean_distance = np.sqrt(np.sum((np.array(features)-np.array(predict))**2))
            #print(euclidean_distance)
            #to je isto kao i gore samo koristimo od numpy-a fje koje su numericki puno optimiziranije
            #moze i euclidean_distance = np.linalg.norm(np.array(features)-np.array(predict)) tu koristimo fje nurme iz paketa za lin algebru
    votes = [i[1] for i in sorted(distances)[:k]]  #sorted(distances) soritira ulazno distances po prvim elementima, u ovom slucaju udaljenost, onda [:k] kaze da uzima sve elemente do k-tog elemnta, [k:] bi bilo do k-tog na dalje, i onda na kraju idem sa i po tih prvih k manjih listi i uzimam i[1] sto su grupe, te grupe spremam jer me ne zanimaju udaljenosti samo grupe   
    vote_result = Counter(votes).most_common(1)[0][0]
    # Collections finds the most common elements. In our case, we just want the single most common, but you can find the top 3 or top 'x.' Without doing the [0][0] part, you get [('r', 3)]. Thus, [0][0] gives us the first element in the tuple. The three you see is how many votes 'r' got.
    return vote_result


dataset = {'k':[[1,2],[2,3],[3,1]], 'r':[[6,5],[7,7],[8,6]]}  # sablona je {ime_klase : array_vrijednosti, ime_klase: array_vrijednosti}
new_features = [5,7]       #ovo ce biti testni podatak

[[plt.scatter(ii[0],ii[1],s=100,color=i) for ii in dataset[i]] for i in dataset]  #za svaki i u datasetu, dataset ima samo 2 to su k i r, za svaki od njih odi sa ii po svim tockama iz te klase i oznaci tocku (ii[0], ii[1]) sa bojom i, s=100 
plt.scatter(new_features[0], new_features[1], s=100) #nakon sta smo pobacali dataset na graf, sad ubacimo i new_features
#predzadnja linija je ista kao i 
#for i in dataset:
#    for ii in dataset[i]:
#        plt.scatter(ii[0],ii[1],s=100,color=i)


result = k_nearest_neighbors(dataset, new_features)
print(result)
plt.scatter(new_features[0], new_features[1], s=100, color = result)  #po coloru zvidimo u koju ga je grupu smjestio
plt.show()  #prikazi graf
