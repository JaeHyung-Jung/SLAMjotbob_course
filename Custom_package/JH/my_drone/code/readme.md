### code explanation
- jhdrone_velocity.cpp : Arming, Takeoff, Move(W.A.S.D), Setposition, RTL, Exit, Get position, Rotate (Recommnded)
- jh_key_finder : Key finder
- jhdrone_position : prototype of move using position
- jhtalker : publish, subscribe test tutorial node
- jhdrone_rotate_all : Contain all ways to rotate (4position, 8position, with PI, velocity, attitude)

---
### Rotate concept

1) Get the current position (x,y,z)

2) Set the pose to move like circle
pos1 (x,y-5,z)
pos2 (x+5,y,z)
pos3 (x,y+5,z)
pos4 (x-5,y,z)

- current position -> pos1 -> pos2 -> pos3 -> pos4 -> pos1 -> current position

3) Quaternion 개념 설명 (짐벌락) 
reference : https://hub1234.tistory.com/21

4) Move with 8pos

5) Move with velocity

6) Move with attitude

7) Move spiral

----
### Euler degree -> Quaternion value

![image](https://user-images.githubusercontent.com/79160507/179910151-6d7db08f-9807-4f7d-b450-e27a177ad35d.png)
- sin, cos graph

![image](https://user-images.githubusercontent.com/79160507/179910198-c5a6e89e-caba-4d4b-8f4d-1a503d75b60c.png)
- sin, cos, quaternion graph

![image](https://user-images.githubusercontent.com/79160507/179910247-d1a601b3-e0ca-4334-acc8-ad7df13e6db5.png)
![image](https://user-images.githubusercontent.com/79160507/179910228-e999b23b-772b-439e-9ad3-a2f6e5debb78.png)

Reference : [Quaternion Converter](https://www.andre-gaschler.com/rotationconverter/)
