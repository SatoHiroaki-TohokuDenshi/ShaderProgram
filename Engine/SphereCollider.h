#pragma once
class SphereCollider {
private:
	float radius_;

public:
	SphereCollider(float _radius);
	float GetRadius() { return(radius_); }
};