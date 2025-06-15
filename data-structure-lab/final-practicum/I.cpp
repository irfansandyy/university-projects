#include <iostream>
#include <vector>

struct Point {
    int x, y;
    Point(int xi, int yi): x(xi), y(yi) {}
};

struct QuadTree {
    int x1, y1, x2, y2;
    QuadTree* children[4];
    Point* person;

    QuadTree(int x1i, int y1i, int x2i, int y2i): x1(x1i), y1(y1i), x2(x2i), y2(y2i), person(nullptr) {
        for (int i = 0; i < 4; ++i) children[i] = nullptr;
    }

    bool isLeaf() const {
        return children[0] == nullptr;
    }

    bool inBoundary(const Point& p) const {
        return p.x >= x1 && p.x < x2 && p.y >= y1 && p.y < y2;
    }

    int count() const {
        if (isLeaf()) return 1;
        int sum = 0;
        for (int i = 0; i < 4; ++i)
            if (children[i]) sum += children[i]->count();
        return sum;
    }

    void insert(Point* p) {
        if (!inBoundary(*p)) return;
        if (x2 - x1 <= 1 && y2 - y1 <= 1) {
            person = p;
            return;
        }

        if (isLeaf() && person == nullptr) {
            person = p;
            return;
        }
        if (isLeaf()) {
            Point* old = person;
            person = nullptr;
            int mx = (x1 + x2) / 2;
            int my = (y1 + y2) / 2;
            children[0] = new QuadTree(x1, y1, mx, my);
            children[1] = new QuadTree(mx, y1, x2, my);
            children[2] = new QuadTree(x1, my, mx, y2);
            children[3] = new QuadTree(mx, my, x2, y2);
            insert(old);
        } 
        for (int i = 0; i < 4; ++i) {
            if (children[i]->inBoundary(*p)) {
                children[i]->insert(p);
                return;
            }
        }
    }
};

int main() {
    int N;
    std::cin >> N;
    std::vector<Point*> points;
    for (int i = 0; i < N; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.push_back(new Point(x, y));
    }
    QuadTree* root = new QuadTree(-101, -101, 101, 101);

    for (auto p : points) root->insert(p);
    std::cout << root->count();

    return 0;
}
