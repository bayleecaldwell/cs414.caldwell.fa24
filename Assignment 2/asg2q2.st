Object >> caseOf: aDictionary ifAbsent: aBlock
    aDictionary keysAndValuesDo: [ :key :value |
        (key value) ifTrue: [ ^ value value ] ].
    ^ aBlock value
