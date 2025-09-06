#pragma once
#include "domain/entities/product.h"
#include "application/repositories/product_repository.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

class InMemoryProductRepository : public IProductRepository
{
private:
    std::unordered_map<int, std::shared_ptr<Product>> storage;

public:
    InMemoryProductRepository() = default;

    std::unique_ptr<Product> getById(int id) override
    {
        auto it = storage.find(id);
        if (it == storage.end())
            throw std::runtime_error("Product not found");

        auto c = it->second;
        return c->copy();
    }

    std::vector<std::unique_ptr<Product>> all() override
    {
        std::vector<std::unique_ptr<Product>> copies;
        for (const auto &[_, p] : storage)
        {
            copies.push_back(p->copy());
        }
        return copies; // RVO
    }

    void save(std::unique_ptr<Product> product) override
    {
        if (!product)
            return;

        storage[product->getId()] = product->copyShared();
    }
};
