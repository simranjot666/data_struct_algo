#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//////////////////////////PROJECT 3 /////////////////////
//DATA STRUCTURES AND ALGORITHMS FALL 2015
//SIMRANJOT S ANTAAL
//
//IDEA:
//This code finds the way from one station to another, using the metro.txt file data
//The idea is to find the path with minimal number of transitions between metro lines, therefore if both stations are on same line then it provides direction, number of
//stations and time to be taken in travel in output trip.txt
//As any given two lines intersect, so if station is not on same line then all possible routes with one transition between the source and destination station are
//evaluated and shortest is selected as final route, similarly directions, number of stations and travelling time is written in trip.txt
//
//METHODOLOGY:
//A linked list is created from metro.txt for every line, and all the corresponding root nodes are stored in 'A' array. each linked list contains all stations on that
//line, color of that line, station name and stopping time.
//Similary another linked list is created for all lines, that stores info about all transition points on that particular line, such as switching time (the same stopping time
//field is resource shared for this purpose), an empty distance field(data field), color of the line to which it tranfers and station name, all root nodes are stored in
//'B' array.
//
//Presence of the source station on all the lines is saved in an array s_cols, whose elements point to corresponding A matrix node , similarly for the destination
//d_cols. To make all possible permutations and combinations w.r.t. source and destination stations.
//
//Going over all combinations of s_cols and d_cols as well as using B matrix info, s_tok_dis array is generated which contains all the useful transition points on
//source line (keeping in mind all the lines that source is on and destination station is on). Similarly d_tok_dis is created with all useful stations info which transition
//to possibly destination. These arrays contain pointers to A matrix color linked lists.
//
//At this point only logic is there to detect if stations are on the same line or not. If they are then travelling time is calculated along with number of stations
//and direction, output is written in trip.txt
//
//Running through all combinations of s_cols,d_cols,s_tok_dis and d_tok_dis. A combination's total travelling time is calculated if it suits following condition
//		color matching between source and the s_tok_dis node, similarly color matching between destination and d_tok_dis
//		same station name for both selected nodes in s_tok_dis and d_tok_dis
//
//Out of all the combinations, the minimum travelling time combination is saved in 'out' array. For this particular combination direction of travel in each of the two
//line travels is found, number of stations travelled on each of the two lines is calculated and output is written in trip.txt
//
//During all the implementations of all methods only A and B matrix nodes are used from switching time calculation to stopping time.
//
// Travelling time when both stations are on same line :
// Time in travel between stations + stoppage time (excluding source and destination station)
//
// Travelling time when stations are on different lines:
// Time in travel between source to transition point + time in travel between transition point and destination + stoppage time (excluding source and transition node)
//  + stoppage time (excluding destination and tranfer station) + switching time at the tranfer station
//
//KNOWN ISSUES:
//(i) this code assumes info in metro.txt format, such as variable declaration is done keeping in mind the structure of metro system etc.
//
//

#define NEW(x) (x*)malloc(sizeof(x))


//Linked list structure to save stations as node containing station name, stop time, color, time distance
typedef struct node {
	int data;
	struct node * next;
	char c[10];
	char st[100];
	int stime;

} NODE;

typedef struct {
	long num;
	char color[10];
	NODE * head;

} ROOT;

NODE * make_node(int data, int stime, char c[], char st[]) {
	NODE * temp;
	temp = NEW(NODE);

	if (temp != NULL) {
		temp->data = data;
		strcpy(temp->c, c);
		strcpy(temp->st, st);
		temp->stime = stime;
		temp->next = NULL;

	}
	return temp;
}

ROOT * make_root(char * color) {
	ROOT * temp;
	temp = NEW(ROOT);

	if (temp != NULL) {
		temp->num = 0;
		temp->head = NULL;
		strcpy(temp->color, color);

	}
	return temp;
}

int insert_at_head(ROOT *r, char *c, char st[], int *d, int *stime) {
	NODE * temp;
	temp = make_node(d, stime, c, st);
	if (temp == NULL)
		return -1;

	if (r == NULL) {
		r = make_root("");
		if (r == NULL)
			return -1;
	}

	(r->num)++;

	if (r->num == 1) {
		temp->next = r->head;

		r->head = temp;
	} else {
		temp->next = r->head;
		r->head = temp;
	}

	return 0;
}

void display_list(ROOT *r) //display contents of the linked list
{
	NODE * temp;

	if (r != NULL) {
		temp = r->head;
		printf("Color of this list is %s\n", r->color);
		do {
			printf("Node Color %s ", temp->c);
			printf("Station %s ", temp->st);
			printf("Distance %d ", (int) temp->data);
			printf("Stop/Switch Time %d\n", (int) temp->stime);

			temp = temp->next;
		} while (temp != NULL);
	}
	printf("\n");
}

// Find and return a node pointer, search either color or station name
NODE * List_find(ROOT *r, char str[], int cORs) {
	NODE * temp;
	if (r != NULL) {
		temp = r->head;
		do {
			if (!cORs) {
				if (strlen(str) == strlen(temp->c)) {
					int cmp = strcmp(str, temp->c);
					if (cmp == 0) {
						return temp;
					}
				}
			} else if (cORs) {
				if (strlen(str) == strlen(temp->st)) {
					int cmp = strcmp(str, temp->st);
					if (cmp == 0) {
						return temp;
					}
				}
			}
			temp = temp->next;

		} while (temp != NULL);
	}

	return NULL;
}

// Calculate all stoppage time and number of stations between temps and tempd nodes
int * stop_time(NODE * temps, NODE * tempd) {
	NODE * tempm = NULL;
	int stopt[2] = { 0, 0 };

	if (tempd->data < temps->data) {
		tempm = temps->next;
		while (strcmp(tempm->st, tempd->st) != 0) {
			stopt[1] += tempm->stime;
			stopt[0] = stopt[0] + 1;
			tempm = tempm->next;
		}
	} else {
		tempm = tempd->next;
		while (strcmp(tempm->st, temps->st) != 0) {
			stopt[1] += tempm->stime;
			stopt[0] = stopt[0] + 1;
			tempm = tempm->next;
		}
	}
	return stopt;

}

//calculate switching time for the selected transfer station
int swit_time(NODE * tempd, NODE * temps, ROOT * B[], int count1) {
	int swit_time = 0;
	NODE * tempn = NULL;
	for (int i = 0; i <= count1; i++) {
		if (!strcmp(B[i]->color, tempd->c)) {

			tempn = B[i]->head;
			do {
				if (!strcmp(tempn->st, tempd->st)
						&& !strcmp(tempn->c, temps->c)) {
					swit_time = tempn->stime;
				}
				tempn = tempn->next;
			} while (tempn->next != NULL);

		}
	}
	return swit_time;

}

int main(int argc, char *argv[]) {
	char s_st[25];
	char d_st[25];

	printf("Enter the starting station : \n");
	scanf("%s", &s_st);
	printf("Enter destination station : \n");
	scanf("%s", &d_st);

	FILE* file = fopen("metro.txt", "r");

	char line[256], op[100];

	int nsp = 0, num_st, temp = 1, temp1 = 1;

	char col_temp[100];

	int count = -2;

	int  z = -2, u, count1 = -1, t9 = 0, switch_time;
	int numSt, dis, swt, sw1, sw2, sw3, sw4, sw5;
	char c1[100], c2[100], c3[100], c4[100];
	char * color;
	NODE * first_st[10]; // as insert_at_head is used so last station is easily accessible but first station needs to be stored
	ROOT * A[10] = { NULL }, *B[10] = { NULL };
	for (int i = 0; i < 10; i++) {
		A[i] = make_root("");
		B[i] = make_root("");
	}

//Store metro.txt data in corresponding color linked lists in A, and save transfer stations of all lines in B
	while (fgets(line, sizeof(line), file)) {
		nsp = 0;
		temp = 1;

		if (count == z) {
			count1++;
			sscanf(line, "%s (%d)", col_temp, &z);
			temp1 = 0;
			count = -2;
			u = 1;
			color = col_temp;
			strcpy(A[count1]->color, color);
			strcpy(B[count1]->color, color);
		}

		for (int i = 0; i < strlen(line); i++) {
			if (nsp) {
				num_st = line[i] - '0';
				if (num_st == 0) {
					sscanf(line, "%s %d %d %d", op, &numSt, &dis, &swt);
					if (u) {
						swt = 0;
						u = 0;
					}
					insert_at_head(A[count1], color, op, dis, swt);

				} else if (num_st == 1) {
					sscanf(line, "%s %d %d %d %s %d", op, &numSt, &dis, &swt,
							c1, &sw1);
					if (u) {
						swt = 0;
						u = 0;
					}
					insert_at_head(A[count1], color, op, dis, swt);
					insert_at_head(B[count1], c1, op, 0, sw1);
				} else if (num_st == 2) {
					sscanf(line, "%s %d %d %d %s %d %s %d", op, &numSt, &dis,
							&swt, c1, &sw1, c2, &sw2);
					if (u) {
						swt = 0;
						u = 0;
					}
					insert_at_head(A[count1], color, op, dis, swt);
					insert_at_head(B[count1], c1, op, 0, sw1);
					insert_at_head(B[count1], c2, op, 0, sw2);
				} else if (num_st == 3) {
					sscanf(line, "%s %d %d %d %s %d %s %d %s %d", op, &numSt,
							&dis, &swt, c1, &sw1, c2, &sw2, c3, &sw3);
					if (u) {
						swt = 0;
						u = 0;
					}
					insert_at_head(A[count1], color, op, dis, swt);
					insert_at_head(B[count1], c1, op, 0, sw1);
					insert_at_head(B[count1], c2, op, 0, sw2);
					insert_at_head(B[count1], c3, op, 0, sw3);
				} else if (num_st == 4) {
					sscanf(line, "%s %d %d %d %s %d %s %d %s %d %s %d", op,
							&numSt, &dis, &swt, c1, &sw1, c2, &sw2, c3, &sw3,
							c4, &sw4);
					if (u) {
						swt = 0;
						u = 0;
					}
					insert_at_head(A[count1], color, op, dis, swt);
					insert_at_head(B[count1], c1, op, 0, sw1);
					insert_at_head(B[count1], c2, op, 0, sw2);
					insert_at_head(B[count1], c3, op, 0, sw3);
					insert_at_head(B[count1], c4, op, 0, sw4);
				}

				temp = 0;
				nsp = 0;
			}
			if (line[i] == 32 && temp)
				nsp = 1;
		}
		if (count == -1)
			first_st[t9++] = A[count1]->head;
		count++;

	}

	FILE *f_out = fopen(argv[1], "w");

	NODE * s_cols[count1];
	NODE * d_cols[count1];
	count = 0;
	int count2 = 0, t1 = 0;
	int same_lines = -1, same_lined = -1, t5, t6;
	int out[4];
	int trip_time = 10000;

	//Presence of the source station on all the lines is saved in an array s_cols, whose elements point to corresponding A matrix node , similarly for the destination
	//d_cols. To make all possible permutations and combinations w.r.t. source and destination stations.
	// also check if both stations are on same line

	for (int i = 0; i <= count1; i++) {
		t1 = 0;
		if (List_find(A[i], s_st, 1) != NULL) {
			s_cols[count] = List_find(A[i], s_st, 1);
			t1 = 1;
			count++;
		}
		if (List_find(A[i], d_st, 1) != NULL) {

			d_cols[count2] = List_find(A[i], d_st, 1);
			if (t1) {
				same_lined = count2;
				same_lines = count - 1;
			}
			count2++;
		}
	}
	NODE * s_tok_dis[100];
	NODE * d_tok_dis[100];
	int count3 = 0, count4 = 0, temp_triptime = 0;
	NODE * tempn = NULL;

	NODE * towards_s, *towards_d;


	//Deal with the case of same line stations
	if (same_lines != -1) {

		for (int i = 0; i <= count1; i++) {
			if (!strcmp(A[i]->color, s_cols[same_lines]->c))
				t5 = i;
		}

		if ((s_cols[same_lines]->data - d_cols[same_lined]->data) < 0) {
			towards_s = A[t5]->head;
		} else {
			towards_s = first_st[t5];
		}
		trip_time = (abs(d_cols[same_lined]->data - s_cols[same_lines]->data)
				+ stop_time(s_cols[same_lines], d_cols[same_lined])[1]);
		fprintf(f_out,
				"Start from %s and continue on same %s line for %d stations towards %s and reach %s in %d minutes and %d seconds\n",
				s_st, d_cols[same_lined]->c,
				stop_time(s_cols[same_lines], d_cols[same_lined])[0] + 1,
				towards_s->st, d_st, trip_time / 60, trip_time % 60);

		// For the case when both stations are on differen lines
	} else {

		for (int p = 0; p < count; p++) { //run through all source node lines
			for (int l = 0; l < count2; l++) { //run through all dest node lines
				for (int i = 0; i <= count1; i++) { // go over all intersection linked lists
					if (!strcmp(B[i]->color, s_cols[p]->c)) { // select only the linked list which is for this particular source line color
						tempn = B[i]->head;
						do {
							if (!strcmp(tempn->c, d_cols[l]->c)) { // select only the nodes in that list which has color equal to this particular dest node color
								for (int k = 0; k <= count1; k++) { // cover all line color which contains all stations

									if (!strcmp(A[k]->color, s_cols[p]->c)) { // if the selected source node color matches = all stations line linked list
										s_tok_dis[count3] = List_find(A[k],
												tempn->st, 1); //find the intersecting station on source line and save it
										if (s_tok_dis[count3] != NULL)
											count3++;
									} else if (!strcmp(A[k]->color,d_cols[l]->c)) { //if the selected dest node color matches = all stations line linked list
										d_tok_dis[count4] = List_find(A[k],
												tempn->st, 1); // find the intersecting station on dest line and save it
										if (d_tok_dis[count4] != NULL)
											count4++;
									}
								}
							}
							tempn = tempn->next;
						} while (tempn != NULL);
					}
				}
			}
		}

		int stopt = 0;

		int count5 = 1;
		for (int i = 0; i < count; i++) {
			for (int k = 0; k < count2; k++) {
				for (int l = 0; l < count3; l++) {
					for (int m = 0; m < count4; m++) {
						if (!strcmp(s_cols[i]->c, s_tok_dis[l]->c)&& !strcmp(d_cols[k]->c, d_tok_dis[m]->c)&& !strcmp(s_tok_dis[l]->st,d_tok_dis[m]->st)) {
// Calculate trip times for all possible combinations of source, dest. (on various lines) and tranfer stations. which satifies above criteria.
							stopt = 0;
							stopt = stop_time(s_cols[i], s_tok_dis[l])[1]
									+ stop_time(d_cols[k], d_tok_dis[m])[1];
							switch_time = swit_time(s_tok_dis[l], d_cols[k], B,count1);

							temp_triptime = abs(s_cols[i]->data - s_tok_dis[l]->data)+ abs(d_cols[k]->data - d_tok_dis[m]->data)+ stopt + switch_time;
							if (trip_time > temp_triptime) {
								trip_time = temp_triptime;
								out[0] = i;
								out[1] = k;
								out[2] = l;
								out[3] = m;
							}
						}
					}
				}
			}
		}


		// Find the direction of travel on both the lines considering the found shortest path
		for (int i = 0; i <= count1; i++) {
			if (!strcmp(A[i]->color, s_cols[out[0]]->c))
				t5 = i;

			if (!strcmp(A[i]->color, d_cols[out[1]]->c))
				t6 = i;
		}

		if ((s_tok_dis[out[2]]->data - s_cols[out[0]]->data) > 0) {
			towards_s = A[t5]->head;
		} else {
			towards_s = first_st[t5];
		}

		if ((d_tok_dis[out[3]]->data - d_cols[out[1]]->data) < 0) {
			towards_d = A[t6]->head;
		} else {
			towards_d = first_st[t6];
		}

		fprintf(f_out,
				"Start from %s station \n take %s line towards %s for %d stations to %s then transfer to %s line \n take %s line towards %s for %d stations to %s \n arrive at %s in %d minutes and %d seconds\n",
				s_cols[out[0]]->st, s_cols[out[0]]->c, towards_s->st,
				stop_time(s_cols[out[0]], s_tok_dis[out[2]])[0] + 1,
				s_tok_dis[out[2]]->st, d_tok_dis[out[3]]->c,
				d_tok_dis[out[3]]->c, towards_d->st,
				stop_time(d_cols[out[1]], d_tok_dis[out[3]])[0] + 1,
				d_cols[out[1]]->st, d_cols[out[1]]->st,

				trip_time / 60, trip_time%60);
	}

	fclose(f_out);
	fclose(file);
	return 0;
}


