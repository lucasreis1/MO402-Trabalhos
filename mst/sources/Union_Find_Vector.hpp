#include "Union_Find.hpp"
#include<vector>

using std::vector;

class Union_Find_Vector: public Union_Find
{
	private:
		struct Node
		{
			int parent;
			int size;
			Node(int p = 0): parent(p),size(1){}
		};

	vector<Node> nodes;

	public:
		Union_Find_Vector(int nel=0);

		void make_set(int x);

		int find_set(int x);

		void _union(int x,int y);

		void link(int x,int y);
};