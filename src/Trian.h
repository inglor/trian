class vertex {
public:
	double x, y, z;
	vertex *next;
// constructor
	vertex(double x1, double y1, double z1) {
		x=x1;
		y=y1;
		z=z1;
		next=NULL;
	}
};

class vertex_list {
public:
	class vertex *head, *tail;
	bool empty;
// constructor	
	vertex_list() {
		head=NULL;
		empty=true;
		tail=NULL;
	}
// method add
	vertex *add(vertex *v1) {
		if(!empty) {
			tail->next=v1;
			tail=v1;
		}	else {
			head=tail=v1;
			empty=false;
		}
		return tail;
	}
// method length
	int length() {
		int i=0;
		vertex *p=head;

		if(empty) return 0;
		else {
			while(p!=NULL) {
				p=p->next;
				i++;
			}
			return i;
		}
	}
// method get
	vertex *get(int i) {
		int j;
		vertex *p=head;

		if(i>=length()) return NULL;
		for(j=0;j<i;j++) p=p->next;
		return p;
	}
};


class triangle {
public:
  vertex *v1, *v2, *v3;
  double cx, cy, r2;
  triangle *next;
// constructor
	triangle(vertex *a1, vertex *a2, vertex *a3) {
		v1=a1;
		v2=a2;
		v3=a3;
			//ta cx,cy isapexoun apo tis koryfes tou trigonou	
			//dioti briskontai ston egkegrammeno kyklo aytou.
		cx=((a2->y-a1->y)*(a3->x*a3->x+a3->y*a3->y)+
				(a3->y-a2->y)*(a1->x*a1->x+a1->y*a1->y)+
				(a1->y-a3->y)*(a2->x*a2->x+a2->y*a2->y))/
				(2*(a1->x*(a3->y-a2->y)+
						a2->x*(a1->y-a3->y)+
						a3->x*(a2->y-a1->y)));
		cy=((a2->x-a1->x)*(a3->y*a3->y+a3->x*a3->x)+
			  (a3->x-a2->x)*(a1->y*a1->y+a1->x*a1->x)+
				(a1->x-a3->x)*(a2->y*a2->y+a2->x*a2->x))/
				(2*(a1->y*(a3->x-a2->x)+
						a2->y*(a1->x-a3->x)+
						a3->y*(a2->x-a1->x)));
		r2=(cx-a1->x)*(cx-a1->x)+(cy-a1->y)*(cy-a1->y);		//Ypologismos tou r*r gia beltistopoiisi
		next=NULL;																				//algori8mou
	}
};

class triangle_list {
public:
	class triangle *head, *tail;
	bool empty;
// constructor	
	triangle_list() {
		head=NULL;
		empty=true;
		tail=NULL;
	}
// method add
	triangle *add(triangle *t1) {
		if(!empty) {
			tail->next=t1;
			tail=t1;
		}	else {
			head=tail=t1;
			empty=false;
		}
		return tail;
	}
// method length		
	int length() {
		int i=0;
		triangle *p=head;

		if(empty) return 0;
		else {
			while(p!=NULL) {
				p=p->next;
				i++;
			}
			return i;
		}
	}
// method get
	triangle *get(int i) {
		int j;
		triangle *p=head;

		if(i>=length()) return NULL;
		for(j=0;j<i;j++) p=p->next;
		return p;
	}
// method remove
	triangle *remove(int i) {
		triangle *p;
		
		if (i>=length()) return NULL;
		if (length()==1) empty=true;
		if (i==0) {
			p=head;
			head=head->next;
			return p;
		} else {
			if (i==length()-1) tail=get(i-1);
			p=get(i);
			get(i-1)->next=p->next;
			return p;
		}
	}
};



class edge {
public:
	class vertex *v1, *v2;
	double d2;
	edge *next;
// constructor	
	edge(vertex *va, vertex *vb) {
		v1=va;
		v2=vb;
		next=NULL;
		d2= ((vb->x-va->x)*(vb->x-va->x))+
				((vb->y-va->y)*(vb->y-va->y))+
				((vb->z-va->z)*(vb->z-va->z));
	}
};

class edge_list {
public:
	class edge *head, *tail;
	bool empty;
// constructor	
	edge_list() {
		head=NULL;
		empty=true;
		tail=NULL;
	}
// method add
	edge *add(edge *e1) {
		if(!empty) {
			tail->next=e1;
			tail=e1;
		} else {
			head=tail=e1;
			empty=false;
		}
		return tail;
	}
// method length		
	int length() {
		int i=0;
		edge *p=head;

		if(empty) return 0;
		else {
			while(p!=NULL) {
				p=p->next;
				i++;
			}
			return i;
		}
	}
// method get
	edge *get(int i) {
		int j;
		edge *p=head;

		if(i>=length()) return NULL;
		for(j=0;j<i;j++) p=p->next;
		return p;
	}
// method remove
	edge *remove(int i) {
		edge *p;
		
		if (i>=length()) return NULL;
		if (length()==1) empty=true;
		if (i==0) {
			p=head;
			head=head->next;
			return p;
		} else {
			if (i==(length()-1)) tail=get(i-1);
			p=get(i-1)->next;
			get(i-1)->next=get(i)->next;
			return p;
		};
	}

};