import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
data = pd.read_csv('Covid19.txt',sep='\s+',header=None)
data = pd.DataFrame(data)
t = data[0]
s = data[1]
i = data[2]
r = data[3]
daily_infection=[]
for day in range(1,len(i)):
    daily_infection.append(i[day]-i[day-1])
data=data.rename(columns={0:'Day',1:'Susecptible',2:'Infected',3:'Removed'})
data=data.set_index('Day')
#print(data.head(600))
print(np.max(daily_infection))
plt.subplots(figsize=(15,10))
plt.plot(t,s,'b',label='Susecptible')
plt.plot(t,i,'r',label='Infected')
plt.plot(t,r,'g',label='Removed')
plt.ylabel('Number of People')
plt.xlabel('Days')
plt.title('COVID19')
plt.legend()
plt.show()











