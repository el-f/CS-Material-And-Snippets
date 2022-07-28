# 54bebed0d5b56c5b2600027f

class Debugger(object):
    attribute_accesses = []
    method_calls = []

class Meta(type):
    def __new__(cls, name, bases, attrs):
        attrs.update({k: tracked_fn(cls, v) for k, v in attrs.items() if callable(v)})
        attrs['__getattribute__']   = tracked_getattr(cls)
        attrs['__setattr__']        = tracked_setattr(cls)
        return type.__new__(cls, name, bases, attrs)

def tracked_getattr(cls):
    def get_wrapper(self, attr):
        val = object.__getattribute__(self, attr)
        Debugger.attribute_accesses.append({
            'action': 'get',
            'class': cls,
            'attribute': attr,
            'value': val
        })
        return val
    return get_wrapper

def tracked_setattr(cls):
    def set_wrapper(self, attr, val):
        object.__setattr__(self, attr, val)
        Debugger.attribute_accesses.append({
            'action': 'set',
            'class': cls,
            'attribute': attr,
            'value': val
        })
    return set_wrapper

def tracked_fn(cls, func):
    def fn_wrapper(*args, **kwargs):
        Debugger.method_calls.append({
            'class': cls,
            'method': func.__name__,
            'args': args,
            'kwargs': kwargs
        })
        return func(*args, **kwargs)
    return fn_wrapper