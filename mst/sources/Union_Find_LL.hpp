#include "Union_Find.hpp"
#include<vector>

using std::vector;

class Union_Find_LL: public Union_Find
{

	private:
		struct Node
		{
			Node *head;
			Node *tail;
			int index;

			Node(int n=1): head(this),tail(NULL), index(n){}
		};

		vector<Node> nodes;
		vector<Node *> components;

	public:
		Union_Find_LL(int nel= 0);

		~Union_Find_LL();

		void make_set(int i);

		int find_set(int x);

		void _union(int x, int y);

		void link(int x, int y);
};