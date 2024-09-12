extern "C"
{
    float FlattenList(float* m_var, int index) 
    {
        return m_var[index];
    }

    float CheckIndex(float* m_var, int value) 
    {
        for(int i = 0; i < sizeof(m_var); i ++)
        {
            if(m_var[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    float DoSomethingToTest(float a, float b)
    {
        return (a + b) / 2;
    }
}