#include "HitableList.h"

HitableList::HitableList(Hitable** l, int n)
{
	_list = l;
	_list_size = n;
}

bool HitableList::hit(Ray& r, float t_min, float t_max, hit_record& rec, std::mt19937& mt) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < _list_size; i++) {
		if (_list[i]->hit(r, t_min, closest_so_far, temp_rec, mt)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

bool HitableList::bounding_box(float t0, float t1, AABB& box) const
{
	if (_list_size < 1)
		return false;
	AABB temp_box;
	bool first_true = _list[0]->bounding_box(t0, t1, temp_box);
	if (!first_true)
		return false;
	else
		box = temp_box;

	for (int i = 1; i < _list_size; i++) {
		if (_list[0]->bounding_box(t0, t1, temp_box))
			box = surrounding_box(box, temp_box);
		else
			return false;
	}
	return true;
}