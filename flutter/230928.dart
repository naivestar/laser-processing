//实时绘制矩形
import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(title: Text('Draw Rectangle')),
        body: DrawRectangleScreen(),
      ),
    );
  }
}

class DrawRectangleScreen extends StatefulWidget {
  @override
  _DrawRectangleScreenState createState() => _DrawRectangleScreenState();
}

class _DrawRectangleScreenState extends State<DrawRectangleScreen> {
  Offset? start;
  Offset? end;
  bool shouldDrawRectangle = false;
  List<Rect> rectangles = [];

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        ElevatedButton(
          onPressed: () {
            setState(() {
              shouldDrawRectangle = true;
            });
          },
          child: Text('Draw Rectangle'),
        ),
        Expanded(
          child: Container(
            color: Colors.orange,
            child: Builder(
              builder: (context) => GestureDetector(
                onPanUpdate: (details) {
                  if (!shouldDrawRectangle) return;
                  if (start == null) {
                    start = details.localPosition;
                  } else {
                    setState(() {
                      end = details.localPosition;
                    });
                  }
                },
                onPanEnd: (details) {
                  if (start != null && end != null) {
                    rectangles.add(Rect.fromPoints(start!, end!));
                  }
                  setState(() {
                    shouldDrawRectangle = false;
                    start = null;
                    end = null;
                  });
                },
                child: CustomPaint(
                  painter: RectanglePainter(rectangles,
                      currentStart: start, currentEnd: end),
                  child: Container(
                    width: double.infinity,
                    height: double.infinity,
                  ),
                ),
              ),
            ),
          ),
        ),
      ],
    );
  }
}

class RectanglePainter extends CustomPainter {
  final List<Rect> rectangles;
  final Offset? currentStart;
  final Offset? currentEnd;

  RectanglePainter(this.rectangles, {this.currentStart, this.currentEnd});

  @override
  void paint(Canvas canvas, Size size) {
    Paint paint = Paint()
      ..color = Colors.black
      ..style = PaintingStyle.stroke;

    for (final rect in rectangles) {
      canvas.drawRect(rect, paint);
    }

    if (currentStart != null && currentEnd != null) {
      canvas.drawRect(Rect.fromPoints(currentStart!, currentEnd!), paint);
    }
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return true;
  }
}
