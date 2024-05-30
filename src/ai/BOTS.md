# Bots

## Scope

This file is about our bots strategy and behaviors 🤖<br>

### Bots Strategy
We use a probability graph to take the worther actions.
* **V1**: We put ourselves the probabilties.

* **V2**: We train a model that calculates probabilities.


## Protocol of messages
* **V1:**
sender->message des IA: signature, message, id_msg<br><br>
* **V2:**<br>
sender->message des IA: signature, message, id_msg<br>
guard resend message->message du guard : signature, guard, message, id_msg