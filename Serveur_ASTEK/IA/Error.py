#!/usr/bin/python
# -*- coding: utf-8 -*-#

class MyException(Exception):
    def __init__(self, Message):
        self.Message = Message
    
    def __str__(self):
        return self.Message
