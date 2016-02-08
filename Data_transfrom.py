#!/usr/bin/env python
# coding=utf-8

import re

def data_transform(data):
    #{"lng":"116.193179","lat":"35.221281"}
    #Latitude:165.99060,Longitude:1040.48340mZ     
    pat = re.compile("Latitude\:([\.|\d]+)\,Longitude\:([\.|\d]+)")
    list = pat.findall(data)
    #print list[0][0],list[0][1]
    if((len(list)<1) or (len(list[0])<2)):
        return '{"lng":"116.193179","lat":"35.221281"}'
    str = '{"lng":"%s","lat":"%s"}' % (list[0][1],list[0][0])
    return str


if __name__ == '__main__':
    data = 'Latitude:165.9999,Longitude:1040.48342'
    ls = data_transform(data)
    print ls
