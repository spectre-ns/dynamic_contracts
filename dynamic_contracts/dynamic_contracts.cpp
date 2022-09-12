// dynamic_contracts.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>



//sweeping contract
class SweepingContract
{
public:
    template<typename T>
    SweepingContract(T strategy) :
        m_pStrategy(std::make_unique<Model<T>>(std::move(strategy)))
    {}

    void Scan2D()
    {
        m_pStrategy->Scan2D();
    }

    void Scan3D()
    {
        m_pStrategy->Scan3D();
    }

private:
    class Concept
    {
    public:
        virtual ~Concept() noexcept = default;
        virtual void Scan2D() = 0;
        virtual void Scan3D() = 0;
    };

    template<typename T>
    class Model : public Concept
    {
    public:
        Model(T strategy) noexcept :
            m_strategy(strategy)
        {}

        void Scan2D()
        {
            m_strategy.Scan2D();
        }

        void Scan3D()
        {
            m_strategy.Scan3D();
        }

    private:
        T m_strategy;
    };

    std::unique_ptr<Concept> m_pStrategy;
};

//illumination contract
class TestContract
{
public:
    template<typename T>
    TestContract(T strategy) :
        m_pStrategy(std::make_unique<Model<T>>(std::move(strategy)))
    {}

    void SetIllumination()
    {
        m_pStrategy->SetIllumination();
    }

    void Scan2D()
    {
        m_pStrategy->Scan2D();
    }

private:
    class Concept
    {
    public:
        virtual ~Concept() noexcept = default;
        virtual void SetIllumination() = 0;
        virtual void Scan2D() = 0;
    };

    template<typename T>
    class Model : public Concept
    {
    public:
        Model(T strategy) noexcept :
            m_strategy(strategy)
        {}

        void SetIllumination()
        {
            m_strategy.SetIllumination();
        }

        void Scan2D()
        {
            m_strategy.Scan2D();
        }

    private:
        T m_strategy;
    };

    std::unique_ptr<Concept> m_pStrategy;
};

//illumination contract
class IlluminationContract
{
public:
    template<typename T>
    IlluminationContract(T strategy) :
        m_pStrategy(std::make_unique<Model<T>>(std::move(strategy)))
    {}

    void SetIllumination()
    {
        m_pStrategy->SetIllumination();
    }

private:
    class Concept
    {
    public:
        virtual ~Concept() noexcept = default;
        virtual void SetIllumination() = 0;
    };

    template<typename T>
    class Model : public Concept
    {
    public:
        Model(T strategy) noexcept : m_strategy(std::move(strategy))
        {}

        void SetIllumination()
        {
            m_strategy.SetIllumination();
        }

    private:
        T m_strategy;
    };

    std::unique_ptr<Concept> m_pStrategy;
};


class HandpieceMk2
{
public:
    void SetIllumination()
    {
        std::cout << "MK2 Illimunation set \n";
    }
};

class EmbeddedMk3
{
public:
    EmbeddedMk3() = default;
    EmbeddedMk3(const EmbeddedMk3&) = delete;
    EmbeddedMk3(EmbeddedMk3&&) = default;
    void SetIllumination()
    {
        std::cout << "MK3 Illimunation set \n";
    }

    void Scan2D()
    {
        std::cout << "MK3 Scanning2D " + std::to_string(_count++) + "\n";
    }

    void Scan3D()
    {
        std::cout << "MK3 Scanning3D \n";
    }
private:
    size_t _count = 0;
};

//Manages the lifetime of the true object
class EmbeddedMk3Manager
{
public:
    EmbeddedMk3Manager(EmbeddedMk3&& handle) :
        pHandle(std::make_shared<EmbeddedMk3>(std::move(handle)))
    {}

    EmbeddedMk3Manager(const EmbeddedMk3Manager&) = default;

    void SetIllumination()
    {
        pHandle->SetIllumination();
    }

    void Scan2D()
    {
        pHandle->Scan2D();
    }

    void Scan3D()
    {
        pHandle->Scan3D();
    }

private:
    std::shared_ptr<EmbeddedMk3> pHandle;
};


class EmbeddedMk2
{
public:
    void Scan2D()
    {
        std::cout << "MK2 Scanning2D \n";
    }

    void Scan3D()
    {
        std::cout << "MK2 Scanning3D \n";
    }
};

void SweepingClient(SweepingContract sweepSource)
{
    sweepSource.Scan2D();
    sweepSource.Scan3D();
}

void IlluminationClient(IlluminationContract illumSource)
{
    illumSource.SetIllumination();
}


int main()
{
    EmbeddedMk2 mk2;
    EmbeddedMk3 mk3;
    HandpieceMk2 mk2_hx;
    EmbeddedMk3Manager wrapper(std::move(mk3));
    auto wrapper2 = wrapper;

    IlluminationClient(std::move(TestContract(wrapper)));
    IlluminationClient(mk2_hx);
    SweepingClient(wrapper);
    SweepingClient(wrapper2);
    SweepingClient(mk2);
}