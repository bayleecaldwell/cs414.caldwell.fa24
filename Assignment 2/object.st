Object subclass: #MyObject
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'MyObjects'

MyObject >> caseOf: aDictionary ifAbsent: aBlock
    aDictionary keysDo: [ :key |
        (key value = self) ifTrue: [ ^ aDictionary at: key ] ].
    ^ aBlock value
