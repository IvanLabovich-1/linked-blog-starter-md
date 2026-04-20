
Mechanical Requirements

| ID    | Parent ID | Functional Requirement                         | Verification |
| ----- | --------- | ---------------------------------------------- | ------------ |
| MR-01 | SR-01     | Board needs to travel 15mph at top speed       | Test-01      |
| MR-02 | SR-02     | Water resistant to a reasonable degree         | Test-02      |
| MR-03 | SR-03     | Go over bumps without breaking or slowing down | Test-03      |
| MR-04 | SR-04     | Well packaged electronics                      |              |


Electrical Requirements

| ID    | Parent ID | Functional Requirement               | Verification |
| ----- | --------- | ------------------------------------ | ------------ |
| ER-01 | SR-05     | Battery life of 1 hour               | Test-04      |
| ER-02 | SR-06     | Emergency motor braking              | Test-05      |
| ER-03 | SR-07     | Drive motor only above minimum speed | Test-06      |


Software/Control Requirements

| ID     | Parent ID | Functional Requirement                                      | Verification |
| ------ | --------- | ----------------------------------------------------------- | ------------ |
| SfR-01 | SR-08     | Controlled by a remote with an ESP32                        | Test-07      |
| SfR-02 | SR-09     | Detect if ESP32 is out of range and stop the board if so    | Test-08      |
| SfR-03 | SR-10     | Deliver correct voltage/current to motor for selected speed | Test-09      |


Integration Requirements

| ID    | Parent ID | Functional Requirement                            | Verification |
| ----- | --------- | ------------------------------------------------- | ------------ |
| IR-01 | SR-11     | Battery, remote, and ESP32 all talk to each other | Test-10      |
| IR-02 | SR-13     | Custom made trucks integrate with existing board  |              |

