import { Controller, Post, Body, Get, Param, Patch, Delete } from '@nestjs/common';
import { Product } from './product.model';
import { ProductsService } from './products.service';

@Controller('products')
export class ProductsController {
    constructor(private readonly productsService: ProductsService) { }


    @Post()
    addProduct(
        @Body('title') prodTitle: string,
        @Body('price') prodPrice: number,
        @Body('description') prodDescription: string
    ): any {
        return this.productsService.insertProduct(prodTitle, prodPrice, prodDescription);
    }

    @Get()
    getAllProducts(): Product[] {
        return this.productsService.getProducts();
    }

    @Get(':id')
    getProduct(@Param('id') prodId: string): Product {
        return this.productsService.getProduct(prodId);
    }
    
    @Patch(':id')
    updateProduct(@Param('id') prodId: string, @Body('title') prodTitle: string, @Body('price') prodPrice: number, @Body('description') prodDescription: string) {
        this.productsService.updateProduct(prodId, prodTitle, prodPrice, prodDescription);
    }

    @Delete(':id')
    deleteProduct(@Param('id') prodId: string) {
        this.productsService.deleteProduct(prodId);
    }
    
}




