#include "Product.h"
#include "Release.h"

int main() {
    Release a = Release();
    Product tempP = Product();
    tempP.setName("A");
    tempP.setProductID(5);
    tempP.setRelease(a);
    tempP.setAnticipatedRelease(true);
    tempP.writeProduct(tempP);
}