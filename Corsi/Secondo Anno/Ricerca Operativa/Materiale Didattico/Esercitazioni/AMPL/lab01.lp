minimize z:
	4*x['x1'] + 2*x['x2'] - 3*x['x3'];

subject to v1['r1']:
	2*x['x1'] + 3*x['x2'] + x['x3'] <= 6;

subject to v1['r2']:
	-4*x['x1'] + 3*x['x2'] - x['x3'] <= 12;

subject to v2['x1']:
	x['x1'] <= 0;

subject to v3['x2']:
	x['x2'] >= 0;

subject to v3['x3']:
	x['x3'] >= 0;

