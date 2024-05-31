# Bots

## Scope

This file is about our bots strategy and behaviors 🤖<br>

### Bots Strategy
We use a probability graph to take the worther actions.
* **V1**: We put ourselves the probabilties.

* **V2**: We train a model that calculates probabilities.

## Ideas to do patterns 📄
We can build paterns by create a set of behaviors by their names like so:
`paterns("look", "take", "broadcast group")`

## Ideas to remove multiple if else if listen 🧽
`
We can store a currentBehavior that contains act and listen functions.
currentBehavior.listen(response)
currentBehavior.act();
updateProbabilities();
updateBehaviors(); // take the worther behavior
`
## Protocol of messages
* **V1:**
sender->message des IA: signature, message, id_msg<br><br>
* **V2:**<br>
sender->message des IA: signature, message, id_msg<br>
guard resend message->message du guard : signature, guard, message, id_msg