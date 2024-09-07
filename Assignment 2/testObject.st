TestCase subclass: #MyObjectTest
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'MyObjects-Tests'

MyObjectTest >> testCaseOfIfAbsent
    | value result |
    value := 3.
    result := value caseOf: {
        [1] -> [ 'Value is 1' ].
        [2] -> [ 'Value is 2' ].
        [3] -> [ 'Value is 3' ].
        [4] -> [ 'Value is 4' ].
    } ifAbsent: [ 'Unknown value' ].
    self assert: result equals: 'Value is 3'

MyObjectTest >> testCaseOfIfAbsentWithUnknownValue
    | value result |
    value := 5.
    result := value caseOf: {
        [1] -> [ 'Value is 1' ].
        [2] -> [ 'Value is 2' ].
        [3] -> [ 'Value is 3' ].
        [4] -> [ 'Value is 4' ].
    } ifAbsent: [ 'Unknown value' ].
    self assert: result equals: 'Unknown value'
