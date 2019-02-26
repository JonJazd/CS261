#ifndef EQ
#define EQ(a, b) (a == b)
#endif

void removeDynArr(struct DynArr *da, TYPE test)
{
    for (int i = 0; i < da->size; i++)
    {
        if (EQ(test, da->data[i]))
        {
            _dynArrayRemoveAt(da, i);
            return;
        }
    }
}

void _dynArrayRemoveAt(struct DynArr *d, int a)
{
    for (int b = a; b < (d->size) - (a + 1); b++)
    {
        d->data[b] = d->data[b + 1];
    }
}

int containsDynArr(struct DynArr *da, TYPE e)
{
    for (int i = 0; i < da->size; i++)
    {
        int compare = da->data[i];
        if (e==compare))
        {
            return 1;
        }
        return 0;
    }
}

/*  1. The removeAt function will do nothing if the argument is not in range.
    2. Since it looks at each spot once and then has to move each spot down the comlpexity in the worst case
    is n^n.
    3. Contains is n in the worst case. Add is n+1 in the worst case as it will copy every value then add 1.
*/