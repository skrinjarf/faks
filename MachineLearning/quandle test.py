# sve je u python 3 pa treba promjenit sintaksu u 2.7, npr print(df.head()) da ide u print df.head()

import pandas as pd
import Quandl
import math
import numpy as np   #ima stvari tipo erase
from sklearn import preprocessing   #ubrzava nesto i moze bit koristno
from sklearn import cross_validation  #razdvaja lijepo podatke
from sklearn import svm             #support vector machine, nesto fancy za regresije isto pali
from sklearn.linear_model import LinearRegression

df=Quandl.get('WIKI/GOOGL')
df = df[['Adj. Open','Adj. High','Adj. Low','Adj. Close','Adj. Volume']]       #izvukao samo zanimljive stupce
df['HL_PTC'] = (df['Adj. High']-df['Adj. Low'])/df['Adj. Low'] * 100.0         #dodao dva stupca is prijasnjih podataka
df['PTC_change'] = (df['Adj. Close']-df['Adj. Open'])/df['Adj. Open'] * 100.0

df = df[['Adj. Close','HL-PTC','PTC_change','Adj. Volume']]                    #ponovno izvukao samo zanimljive stupce

forecast_col = 'Adj. Close'                          #koristi close kao stupac kojeg ce predvidat   

df.fillna(-99999, inplace=True)                      #napuni sve prazne podatke sa -99 999 da ne budu nan (kao null) jer sa njima nemoze radit u machine learningu
forecast_out= int(math.ceil(0.01*len(df)))           #broj kastan u int koji mu uzima strop od 1 posto * mjera za podatke

df['label'] = df[forecast_col].shift(-forecast_out)  #novi stupac sa predvidanjima koji ce biti isti kao forcastan stupac tj adj.Close shiftan za prije definiran broj u negativno (buducnost)
                                                     #taj shift je fj u pandas koja tu sama napravi predvidanje nekako
df.dropna(inplace=True)                              #ispusti one prazne brojeve, da bude ljepsi ispis
print(df.head())                                     #ispise sve podatke sa dodatnim stupcom label koji ima predvidanja pomaknuta za 1 posto u buducnost


x= np.array( df.drop(['label'],1) )   # u x nam drzi sve supce sa podatcima osim labele. to su tzv. FEATURES
y=np.array(df['label'])               #y drzi samo label tzv LABEL sto su podatci koji nas zanimaju

x=preprocessing.scale(x)             #to stavlja podatke u neki normalni raspored sa ostalim podatcima. da se scalea kako spada trebalo bi ga feedat sa ostlaim training podatcima, a to onda trosi procesorsku moc. trebalo bi scaleat sve nove podatke sali ne same za sebe nego uz njih treba scaleat i sve ostale vrijednosti sto postane sporo pa se obicno koristi samo za ne jako dinamicne podatke. nesto sto se rijetko mjenja

y = np.array(df['label'])

x_train, x_test, y_train, y_test = cross_validation.train_test_split(x,y, test_size=0.2)  #ova fja proshuffla podatke da nebude nekih byasseva i onda ih pobaca u one varijable, bitan je poredak varijabli, onda cemo training varijable(podatke) koristim za treniranje CLASSIFIERA 
#train test split zapravo podjeli podatke na testne i na podatke za treniranje, i onda na temelju jednih podataka treniram fju a i testiram ih na drugim podatcima
klasifajer = LinearRegression( n_jobs=10 ) #ovaj n_jobs se moze ispustit, to govori koliki stupanj paralelizma mu se dozvojava, defaultno je 1, za maksimalno moguce moze se stavit -1. umjesto LinearRegression mogli smo staviti svm.SVM koji bi koristi vektorsko predivdanje
klasifajer.fit(x_train, y_train)    #ovim istreniram klasifajer sta je fja predivdanja i ovom slucaju je to linearna fja
preciznost = klasifajer.score(x_test,y_test)  #score mi daje koliko dobro moja fja pogada podatke,

print(preciznost)  #standardno ide prkeo najmanjih kvadrata
