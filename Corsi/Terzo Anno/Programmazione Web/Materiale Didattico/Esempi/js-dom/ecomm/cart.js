"use strict";
const products = [
    {'id': 1, 'description': 'pasta', 'price': 1.5, 'availability': 10},
    {'id': 2, 'description': 'bread', 'price': 1.0, 'availability': 20},
    {'id': 3, 'description': 'milk', 'price': 0.5, 'availability': 30},
    {'id': 4, 'description': 'eggs', 'price': 2.0, 'availability': 15},
    {'id': 5, 'description': 'cheese', 'price': 3.0, 'availability': 5}
];

let cart = {
    items: [],
    total_price: 0,
    addItem(productId, quantity) {
        const product = products.find(p => p.id === productId);
        if (product && product.availability >= quantity) {
            this.items.push({ product, quantity });
            product.availability -= quantity;
            this.total_price = this.items.reduce((acc, item) => acc + item.product.price * item.quantity, 0);
        } else {
            console.log('Product not available in the requested quantity.');
        }
    },  
    clearCart() {
        this.items.forEach(item => {
            item.product.availability += item.quantity;
        });
        this.items = [];
        this.total_price = 0;
    }
}