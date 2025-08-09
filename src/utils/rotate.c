#include <miniRT.h>

t_vec3 rotate(t_vec3 v, t_vec3 rowx, t_vec3 rowy, t_vec3 rowz)
{
    t_vec3 out;

    out.x = v.x * rowx.x + v.y * rowx.y + v.z * rowx.z;
    out.y = v.x * rowy.x + v.y * rowy.y + v.z * rowy.z;
    out.z = v.x * rowz.x + v.y * rowz.y + v.z * rowz.z;
    return out;
}

t_vec3 rotate_x(t_vec3 v, float a)
{
    return rotate(v,
        (t_vec3){1, 0, 0},
        (t_vec3){0, cos(a), -sin(a)},
        (t_vec3){0, sin(a),  cos(a)}
    );
}

t_vec3 rotate_y(t_vec3 v, float a)
{
    return rotate(v,
        (t_vec3){cos(a), 0, sin(a)},
        (t_vec3){ 0, 1, 0},
        (t_vec3){-sin(a),  0, cos(a)}
    );
}

t_vec3 rotate_z(t_vec3 v, float a)
{
    return rotate(v,
        (t_vec3){cos(a), -sin(a), 0},
        (t_vec3){sin(a),  cos(a), 0},
        (t_vec3){0, 0, 1}
    );
}
