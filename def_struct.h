#ifndef DEF_STRUCT_H
#define DEF_STRUCT_H
typedef struct tagScreen
{
    int width;
    int height;
    int index;
    tagScreen()
    {
        memset(this,0,sizeof(tagScreen));
    }
}SCREEN;

#endif // DEF_STRUCT_H
