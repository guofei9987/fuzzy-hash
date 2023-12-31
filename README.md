# fuzzy-hash

This project computes fuzzy hash.  

## install


If `gcc` is not installed, execute the following command to install `gcc`:

```bach
apt update
apt install gcc -y
```

Then install `fuzzy-hash`
```bash
pip install fuzzy-hash
```



```python
from fuzzy_hash import fuzzy_hash, fuzzy_compare

sentence = '''
近期，有一部热播硬核电视剧引发全网关注。与其他硬核电视剧不同的是，这部电视剧真的硬“核”，含“核”量高达100%。这就是《许你万家灯火》——首部全景反映我国核电工业发展历程的电视剧。
《许你万家灯火》极具年代感，这是因为取景地之一是中国核动力的发源地——九〇九基地。
中国第一代核潜艇研发实验基地
也是中国核动力研究设计院的前身

剧组在基地里面内置景，1:1复刻了主要场景十余个，包括第一座陆上模式堆主控室、核电大院、核电办公楼、核电家属楼、零号点、医院、图书馆、大礼堂等，高度还原了老一辈核工业人的研发和生活环境。

而《许你万家灯火》的创作题材，便是中国完全自主知识产权的三代核电技术——“华龙一号”。
从核潜艇研发起步的中国核工业
如何实现拥有世界一流核电站的梦想？
'''
sentence2 = sentence.replace('电视剧', '视频')
sentence2 += "添加几句结尾"

hash1 = fuzzy_hash(sentence.encode('utf-8'))
hash2 = fuzzy_hash(sentence2.encode('utf-8'))

print(hash1)
print(hash2)

corr = fuzzy_compare(hash1, hash2)
print('corr = {}%'.format(corr))
```

outputs:
>b'24:NCRqxthHjDYTvxiiIhNM+Nkr6gy8C4xB66R514cLCxdAtXKlru2uEj:tBH4TdN+OuNOprIxRAa'  
b'24:NocPinHjDYTvxiiISxM+Nkr6gy8C4xB66R514cLCxdAtXKlru2uExi2dx:2cPinH4Tda+OuNOprIxRASLdx'  
corr = 82%





# See Also 

- ssdeep
- Jesse D. Kornblum, "Identifying almost identical files using context 
triggered piecewise hashing", Digital Investigaton, 3(S):91-97, 
September 2006, [http://dx.doi.org/10.1016/j.diin.2006.06.015](http://dx.doi.org/10.1016/j.diin.2006.06.015),
The Proceedings of the 6th Annual Digital Forensic Research Workshop