"Counter class definition"
Object subclass: #Counter
    instanceVariableNames: 'count'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'CounterDemo'.

Counter >> initialize
    count := 0.

Counter >> increment
    count := count + 1.
    self changed: #count.

Counter >> decrement
    count := count - 1.
    self changed: #count.

Counter >> count
    ^ count.


"CounterView class definition"
PluggableTextMorph subclass: #CounterView
    instanceVariableNames: ''
    classVariableNames: ''
    poolDictionaries: ''
    category: 'CounterDemo'.

CounterView >> update: aSymbol
    aSymbol = #count ifTrue: [
        self contents: (self model count asString)
    ].


"CounterController class definition"
Object subclass: #CounterController
    instanceVariableNames: 'model'
    classVariableNames: ''
    poolDictionaries: ''
    category: 'CounterDemo'.

CounterController >> model: aModel
    model := aModel.

CounterController >> increment
    model increment.

CounterController >> decrement
    model decrement.


"Set up UI and connect the components"
| model view controller incrementButton decrementButton |
model := Counter new.
view := CounterView new model: model.
controller := CounterController new model: model.

"Open the view in the Squeak world"
view openInWorld.

"Create the Increment button"
incrementButton := SimpleButtonMorph new.
incrementButton label: 'Increment'.
incrementButton target: controller.
incrementButton actionSelector: #increment.
incrementButton openInWorld.

"Create the Decrement button"
decrementButton := SimpleButtonMorph new.
decrementButton label: 'Decrement'.
decrementButton target: controller.
decrementButton actionSelector: #decrement.
decrementButton openInWorld.
 Z