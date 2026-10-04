template<typename T>
struct Point {
    // Everything public, as it is struct.
    T x, y;
    Point(T xVal, T yVal): x(xVal), y(yVal) {}
    Point& operator+=(const Point& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Point operator+(const Point& v) const {return Point(x+v.x, y+v.y);}
    Point operator*(const Point& v) const {return Point(x*v.x - y*v.y, x*v.y + y*v.x);}
    template<typename U>
    Point(const Point<U>& v)
        : x(static_cast<T>(v.x)),
          y(static_cast<T>(v.y))
    {}
};

Point<int> rot_90(Point<int> point) {
    Point<int> _i(0, -1);
    return _i*point;
}

inline Point<int> rot_90_(const Point<int>& point) {
    auto [a,b] = point;
    return Point(b, -a);
}

class Solution {
private:
    inline bool acceptable(Point<int> pos, int minRow, int maxRow, int minColumn, int maxColumn) {
        return pos.x >= minRow && pos.x <= maxRow && 
            pos.y >= minColumn && pos.y <= maxColumn;
    }
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> result;
        Point<int> direction{0,1}, pos{0,0};
        int minColumn=0, minRow=0, maxRow=m-1, maxColumn=n-1; 
        for (int i=0; i < m*n; i++) {
            result.push_back(matrix[pos.x][pos.y]);
            if (!acceptable(pos+direction, minRow, maxRow, minColumn, maxColumn))  {
                direction = rot_90_(direction);
                if (direction.x == 1)
                    minRow++;
                else if (direction.x == -1)
                    maxRow--;
                else if (direction.y == 1)
                    minColumn++;
                else
                    maxColumn--;
            }
            pos += direction;
        }
        return result;
    }
};