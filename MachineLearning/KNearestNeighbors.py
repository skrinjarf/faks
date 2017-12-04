import numpy as np
from sklearn import preprocessing, cross_validation, neighbors
import pandas as pd

#trazimo da program odreduje sta je maligni a sta benigni tumor , class je atribut koji to govori, a id je id pacjenta, uz puno drugih atributa vezanih za rak 

df = pd.read_csv('breast_cancer_data')  #breast_cancer_data je txt file u direktoriju iz kojeg citamo podatke
df.replace('?',-99999, inplace=True) #u specifikaciji je dano da su nepoznate vrijednosti oznacene sa ?

df.drop(['id'],1, inplace= True)  #dropa id zato jer je kneares neighborst UZASNO osjetljiv na podatke koji ne utjecu na rezultat, kao sta tu id pacjenta ne utjece na vrstu tumora

x= np.array(df.drop(['class'],1))  #vjerojatno dropaj od class iducih 1 stupaca; da smo u drop dodali inplace=True onda bi to zapravo promjenilo df, ovako ga ne mjenja
y= np.array(df['class'])

x_train, x_test, y_train, y_test = cross_validation.train_test_split(x,y,test_size=0.2)

klasifajer = neighbors.KNeighborsClassifier()
klasifajer.fit(x_train,y_train)

accuracy = klasifajer.score(x_test,y_test)
print accuracy

primjer = np.array([4,2,1,1,1,2,3,2,1])  #ocekujem 2 (benigni)
primjer = primjer.reshape(1,-1) #bez toga baca neki error da nije sve u dobrom shapeu jer smo dodali ovaj primjer

predvidanje = klasifajer.predict(primjer)
print predvidanje


primjer = np.array([[4,2,1,1,1,2,3,2,1],[4,2,2,2,1,2,3,2,1]])  #ocekujem 2 (benigni)
primjer = primjer.reshape(2,-1) #sad ide 2 jer imamo 2 primjera gore ubacena
#ZA NEPOZNATI BROJ PRIMJERA MOZEMO STAVIT len(primjer)

predvidanje = klasifajer.predict(primjer)
print predvidanje

#za spremanje klasifajera da ga nemoramo trenirat stalno iznova i trosit vrijeme mozemo koristit PICKLE, to je neki pythonov folder koji onda sprema te stvari pa se od tamo moze samo loadat klasifajer jer na velikim podatcima treniranje moze trajat i u danima
