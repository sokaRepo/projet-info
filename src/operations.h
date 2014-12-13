#ifndef OPERATIONS
#define OPERATIONS

int getPolyLength(dev poly);
void swap_p(dev *p1, dev *p2);
void sortF(dev *poly);
int addMonomial(dev *poly);
void cleanNullMonomial(dev *poly);
void addPoly(dev poly1, dev poly2, dev * result);
void multiplyPoly(dev poly1, dev poly2, dev * result);
void soustractPoly(dev poly1, dev poly2, dev * result);
void dividePoly(dev poly1, dev poly2, dev * result);

#endif