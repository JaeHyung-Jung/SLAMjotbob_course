### code explanation
- jhdrone : finished version
- jhdrone_velocity.cpp : Arming, Takeoff, Move(W.A.S.D), Setposition, RTL, Exit, Get position, Rotate (Recommnded)
- jh_key_finder : Key finder
- jhdrone_position : prototype of move using position
- jhtalker : publish, subscribe test tutorial node
- jhdrone_rotate_all : Contain all ways to rotate (4position, 8position, with PI, velocity, attitude)

---
### Euler degree -> Quaternion value

![image](https://user-images.githubusercontent.com/79160507/180125127-151395ea-7265-4782-b3da-34a64deef9e3.png)
- sin, cos graph

![image](https://user-images.githubusercontent.com/79160507/180125146-6dc91eca-fba3-43b3-b027-e149cfe47f42.png)
- sin, cos, quaternion graph

![image](https://user-images.githubusercontent.com/79160507/179910247-d1a601b3-e0ca-4334-acc8-ad7df13e6db5.png)
![image](https://user-images.githubusercontent.com/79160507/179910228-e999b23b-772b-439e-9ad3-a2f6e5debb78.png)

Reference : [Quaternion Converter](https://www.andre-gaschler.com/rotationconverter/) <br>
Reference : https://hub1234.tistory.com/21

---
### Rotate concept
#### 1. Rotate with 4 pos
![image](https://user-images.githubusercontent.com/79160507/180117809-40bdf40f-f836-4e65-9f8a-5b56ff5d055c.png)

#### 2. Rotate with 8 pos
![image](https://user-images.githubusercontent.com/79160507/180117881-5e8fd1b7-bfd9-44b5-b413-6cdf9474d69b.png)

#### 3. Rotate with radian, degree position 
![image](https://user-images.githubusercontent.com/79160507/180117939-e150e6ad-dcb7-4134-9e01-3d36e7070efb.png)

#### 4. Heading to center with quaternion value
![image](https://user-images.githubusercontent.com/79160507/180118033-4ec8e297-9216-444f-b388-be0a34bd77f9.png)

#### 5. Rotate with velocity using Vertical Vector
![image](https://user-images.githubusercontent.com/79160507/180185908-b15e1067-80dc-4783-8b54-eefd1083abc5.png)

#### 6. Rotate with velocity : Previous vector operation
![image](https://user-images.githubusercontent.com/79160507/180185989-d639f45d-c991-4a55-a460-684cf3c52303.png)

----

