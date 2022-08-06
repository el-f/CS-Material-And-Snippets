import { Injectable , NotFoundException } from "@nestjs/common";
import { Product } from "./product.model";

const ID_LENGTH = 3;

function IDGenerator(): string {
    return Math.random().toString(36).substring(2, ID_LENGTH + 2);
}

@Injectable()
export class ProductsService {
    private products: Product[] = [];
    
    getProducts(): Product[] {
        return this.products.slice(); // return a copy of the array to not return the reference
    }

    private getProductById(prodId: string) : [Product, number] {
        const prodIdx = this.products.findIndex(product => product.id === prodId);
        const prod: Product = this.products[prodIdx];
        if (!prod) {
            throw new NotFoundException('Product not found');
        }
        return [prod, prodIdx];
    }

    getProduct(prodId: string): Product {
        const product: Product = this.getProductById(prodId)[0];
        return { ...product }; // copy the product object to not return the reference
    }

    insertProduct(title: string, price: number, description: string) {
        const product = new Product(IDGenerator(), title, price, description);
        console.log(product);
        this.products.push(product);
        return { ...product }; // copy the product object to not return the reference
    }

    updateProduct(prodId: string, prodTitle: string, prodPrice: number, prodDescription: string) {
        const [product, prodIdx] = this.getProductById(prodId);
        const updatedProduct = { ...product };
        if (prodTitle) {
            updatedProduct.title = prodTitle;
        }
        if (prodPrice) {
            updatedProduct.price = prodPrice;
        }
        if (prodDescription) {
            updatedProduct.description = prodDescription;
        }
        this.products[prodIdx] = updatedProduct;

        return { ...updatedProduct }; // copy the product object to not return the reference

    }

    deleteProduct(prodId: string) {
        const prodIdx = this.products.findIndex(product => product.id === prodId);
        if (prodIdx === -1) {
            throw new NotFoundException('Product not found');
        }
        this.products.splice(prodIdx, 1);
    }

}