---
title: OpenGL Transform Feedback
date: 2021-05-08 09:04:30
author: luc@sietium.com
tags: [OpenGL]
categories: graphics
toc-depth: 1
---

# 为什么要有[TF](https://www.khronos.org/opengl/wiki/Transform_Feedback)

**Transform Feedback**(xfb)是将Vertex_Processing阶段产生的图元的顶点属性(vertex attributes)保存(record/capture)在**Buffer Objects**, 以便后面重复使用。这样做的一个好处是所记录的顶点数据被作为一个顶点属性数组(vertex attributes array)保存在显存，这样就省去了让CPU干预拷贝数据的麻烦，GPU可以直接使用这些属性。

<!--more-->

# OpenGL哪个版本引入TF

Transform Feedback最常见的应用是在构建粒子系统(Particle System), 它是在OpenGL 3.0之后被引入的，而DirectX10引入类似的功能更早一些，在DirectX10中，它被叫做**Stream Output**.

![OpenGL 3.1 Pipeline](opengl-xfb/tf-gles-31.jpg)

# [Vertex Processing](https://www.khronos.org/opengl/wiki/Vertex_Processing)
**xfb**的输入来自Vertex Processing, 所以首先要确定Vertex Processing阶段都是什么，输出什么。Vertex Processing的输出是图元(Primitives), 它至少包含一个vertex shader.

| Stage        | Presence       |
|:-------------|:---------------|
| vertex       | required       |
| tessellation | optional       |
| geometry     | optional       |

# Capturing

当Vertex Processing最后的shader是geometry或tessellation evaluation时，则所记录的图元就是geometry或tessellation evaluation输出的图元，否则那些顶点数据来自vertex shader. 另外所记录的顶点数据也不一定都保存在同一个buffer里，这即为`bufferMode`的含义。

## Capturing Setting
```
void glTransformFeedbackVaryings(GLuint program,
				 GLsizei count,
				 const char **varyings,
				 GLenum bufferMode);
```

这个API设置:
- 哪些program的输出变量被**captured**
- capturing模式， capturing模式有两种

    - `GL_INTERLEAVED_ATTRIBS`
    - `GL_SEPARATE_ATTRIBS`

### interleaved mode
这种模式下，所有captured的输出被保存在同一个buffer object.

### separate mode
这种模式下，输出未必被captured到不同的buffer object, 它仅仅是指输出被captured到不同的**buffer binding points**. 因为同一个buffer object的不同区域也可以被绑定到不同的**buffer binding points**.

## Captured Output Variables

那么可以记录的顶点属性有多少个呢？大小如何？

### 多少顶点属性或总共多少数据可以被记录

- separate capture

| Limitation                                       | Minimal Value |
|:-------------------------------------------------|:-------------:|
| GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS       | 4             |
| GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS    | 4             |

- interleaved capture

| Limitation                                       | Minimal Value |
|:-------------------------------------------------|:-------------:|
| GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS | 64            |

- advanced interleaved capture (不同的变量放在不同的buffers)

| Limitation                                       | Minimal Value |
|:-------------------------------------------------|:-------------:|
| GL_MAX_TRANSFORM_FEEDBACK_BUFFERS                | 64            |

注意到在interleaved capture mode下，没有顶点属性个数的限制，原因是在interleaved mode下，所有顶点属性都是在同一个buffer中，所以限制了总的components的个数后，无论你记录多少个属性，这些属性总的components个数不能超过这个最大值, 而在separate mode下，每个列出的变量是保存在各自不同的buffer中，所以除了对components设限外，还要对属性个数设限。所以这里`GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS`的一个更好的名字应该是`GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_BUFFERS`.

### 顶点属性的数据类型是什么

- structs
- arrays
- members of interface blocks

# Buffer Binding
当设置好要capturing program中的哪些输出变量，以何种模式captured后，接下来就要设置(申请)保存captured的数据的buffer objects.

```
void glBindBufferRange(GLenum target,
		       GLuint index,
		       GLuint buffer,
		       GLintptr offset,
		       GLsizeiptr size);
```

这里`target`就是`GL_TRANSFORM_FEEDBACK_BUFFER`. `offset`必须是4字节对齐，如果存进buffer的值包含**double-precision**, 则需要8字节对齐。

# Feedback Process
Capture设置好，Buffer绑定好之后，就可以开始**Recording** Vertex Processing产出的数据了。通过调用下面的API开始Feedback:
```
void glBeginTransformFeedback(GLenum primitiveMode);
```

这里`primitiveMode`只能是以下3种之一:
- GL_POINTS
- GL_LINES
- GL_TRIANGLES

Transform Feedback模式被激活后，在没有调用`glPauseTransformFeedback`或`glEndTransformFeedback`之前，以下行为不被允许:

- 修改`GL_TRANSFORM_FEEDBACK_BUFFER`的bindings
- 任何对这些绑定的`GL_TRANSFORM_FEEDBACK_BUFFER`的读写操作
- 重新申请这些绑定的`GL_TRANSFORM_FEEDBACK_BUFFER`的存储
- 修改当前使用的program, 也就是不能调用`glUseProgram`或`glBindProgramPipeline`, 还有`glUseProgramStages`

即出Transform Feedback模式调用:

```
void glEndTransformFeedback();
```

# Feedback Objects
跟其它OpenGL的功能一样，Transform Feedback也有一大堆state需要track, 所以这些state被封装进**Transform Feedback Objects**, 这些Feedback Objects和其它OpenGL Object一样需要`Gen`, `Delete`和`Bind`:

```
void glGenTransformFeedbacks(GLsizei n, GLuint *ids);
void glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids);
void glBindTransformFeedback(GLenum target, GLuint id);
```

NOTE:
- `glBindTransformFeedback`的`target`永远是`GL_TRANSFORM_FEEDBACK`
- 不能绑定一个Feedback Object，如果当前的Feedback Object还是active或没有被paused.

那么Feedback Object里封装了哪些Transform Feedback state呢？
- generic buffer bindings, 即调用`glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, ...)`绑定的那些buffers
- indexed buffer bindings, 即调用`glBindBufferRange(GL_TRANSFORM_FEEDBACK, ...)`绑定的那些buffers
- transform feedback是否是active还是paused
- 被当前的feedback操作记录的count of primitives等等

# Feedback Rendering
OK, 我们现在获得了Vertex Processing的结果，并记录了这次Transform Feedback操作的状态到Transform Feedback Objects(例如captured count of primitives, the number of vertices). 但是我们如何利用这些captured数据呢？

```
void glDrawTransformFeedback(GLenum mode,
			     GLuint id);

void glDrawTransformFeedbackInstanced(GLenum mode,
				      GLuint id,
				      GLsizei instancecount);
void glDrawTransformFeedbackStream(GLenum mode,
				   GLuint id,
				   GLuint stream);
void glDrawTransformFeedbackStreamInstanced(GLenum mode,
					    GLuint id,
					    GLuint stream,
					    GLsizei instancecount);
```

NOTE:
- 在调用这些`Draw`命令前，一定要先调用`glEndTransformFeedback`, 因为只有当调用了`glEndTransformFeedback`后，OpenGL状态机才知道一次完整的Transform Feedback操作完成了。

