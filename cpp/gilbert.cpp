#include <boost/coroutine2/all.hpp>
#include <iostream>

const int u = 1;  // pixel step

int offset_1[] = { u, -u, 0, 0 };
int offset_2[] = { 0, 0, -u, u };

struct Gilbert {
    using value_type = std::pair<int, int>;
    using push_type = boost::coroutines2::coroutine<value_type>::push_type;
    using pull_type = boost::coroutines2::coroutine<value_type>::pull_type;

    Gilbert(int max_level)
        : coro{[max_level, this](push_type& result){
            start(result, max_level);
        }}
    {

    }

    bool has_next()
    {
        return static_cast<bool>(coro);
    }

    value_type next()
    {
        auto ret = coro.get();
        coro();
        return ret;
    }


private:
    // BGI emulation
    void linerel(push_type& result, int x,int y)
    {
        glx+=x;
        gly+=y;
        //printf("%d,%d\n",glx,gly);
        result({glx,gly});
    }

    void moveto(push_type& result, int x,int y)
    {
        glx=x;
        gly=y;
        //printf("%d,%d\n",glx,gly);
        result({glx,gly});
    }


    // Elements of curve
    void a(push_type& result, int i)
    {
        if (i > 0)
        {
            d(result, i-1);
            linerel(result, +u,0);
            a(result, i-1);
            linerel(result, 0, u);
            a(result, i - 1);
            linerel(result, -u, 0);
            c(result, i - 1);
        }
    }

    void b(push_type& result, int i)
    {
        if (i > 0)
        {
            c(result, i - 1);
             linerel(result, -u, 0);
             b(result, i - 1);
             linerel(result, 0, -u);
             b(result, i - 1);
             linerel(result, u, 0);
            d(result, i - 1);
        }
    }

    void c(push_type& result, int i)
    {
        if (i > 0)
        {
            b(result, i - 1);
            linerel(result, 0, -u);
            c(result, i - 1);
            linerel(result, -u, 0);
            c(result, i - 1);
            linerel(result, 0, u);
            a(result, i - 1);
        }
    }

    void d(push_type& result, int i)
    {
        if (i > 0)
        {
            a(result, i - 1);
            linerel(result, 0, u);
            d(result, i - 1);
            linerel(result, u, 0);
            d(result, i - 1);
            linerel(result, 0, -u);
            b(result, i - 1);
        }
    }


    // Nearest to power of 2
    unsigned int flp2(unsigned int x){
        x = x | (x>>1);
        x = x | (x>>2);
        x = x | (x>>4);
        x = x | (x>>8);
        x = x | (x>>16);
        return x - (x >> 1);
    }

    void start(push_type& result, int max_level)
    {
        moveto(result, 0, 0);
        a(result, max_level);
    }


private:
    pull_type coro;
    int glx;
    int gly;
};

int main()
{

    Gilbert gen(2);

    while (gen.has_next()) {
        auto v = gen.next();
        std::cout << v.first << "," << v.second << std::endl;
    }

    return 0;
}